#include "preprocessor.h"
#include "looreflect.h"
#include "outputrevision.h"
#include "ghc/fs_std.hpp"
#include "ghc/fs_utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include "commandlineoption.h"
#include "commandlineparser.h"
#include "looarguments.h"

#include <codecvt>

//获取环境变量
QByteArray qgetenv (const char *varName)
{
	//QMutexLocker locker (&environmentMutex);
#if defined(_MSC_VER) && _MSC_VER >= 1400
	size_t requiredSize = 0;
	QByteArray buffer;
	getenv_s (&requiredSize, 0, 0, varName);
	if (requiredSize == 0)
		return buffer;
	buffer.resize (int (requiredSize));
	getenv_s (&requiredSize, &buffer[0], requiredSize, varName);
	// requiredSize includes the terminating null, which we don't want.
	assert (*(buffer.rbegin ()) == ('\0'));
	buffer.resize (buffer.size () - 1);
	return buffer;
#else
	return QByteArray (::getenv (varName));
#endif
}

namespace loo
{
	LooArguments g_LooArguments;
	/*
	This function looks at two file names and returns the name of the
	infile with a path relative to outfile.

	Examples:

		/tmp/abc, /tmp/bcd -> abc
		xyz/a/bc, xyz/b/ac -> ../a/bc
		/tmp/abc, xyz/klm -> /tmp/abc
	*/
	static QByteArray combinePath (const std::string &infile, const std::string &outfile)
	{
		fs::directory_entry inFileInfo (fs::combine_path_file(fs::current_path (),infile));
		fs::directory_entry outFileInfo (fs::combine_path_file (fs::current_path (), outfile));
		//为了获得inFileInfo相对于outFileInfo.dir ()得相对路径
	
		const QByteArray relativePath = fs::relative (inFileInfo.path (), outFileInfo.path ().root_directory ()).string();
		//const QByteArray relativePath = QFile::encodeName (outFileInfo.dir ().relativeFilePath (inFileInfo.filePath ()));
#if defined(_MSC_VER)
		if (outFileInfo.path ().root_directory ().string ().length () + relativePath.length () + 1 >= 260)
		{
			//todo
		}
#endif
//#ifdef LOO_OS_WIN
//		// It's a system limitation.
//		// It depends on the Win API function which is used by the program to open files.
//		// cl apparently uses the functions that have the MAX_PATH limitation.
//		if (outFileInfo.dir ().absolutePath ().length () + relativePath.length () + 1 >= 260)
//			return QFile::encodeName (inFileInfo.absoluteFilePath ());
//#endif
		return relativePath;
	}

	void error (const char *msg = "Invalid argument")
	{
		if (msg)
			fprintf (stderr, "moc: %s\n", msg);
	}

	static inline bool hasNext (const Symbols &symbols, int i)
	{
		return (i < symbols.size ());
	}

	static inline const Symbol &next (const Symbols &symbols, int &i)
	{
		return symbols.at (i++);
	}


	QByteArray composePreprocessorOutput (const Symbols &symbols) {
		QByteArray output;
		int lineNum = 1;
		Token last = PP_NOTOKEN;
		Token secondlast = last;
		int i = 0;
		while (hasNext (symbols, i)) {
			Symbol sym = next (symbols, i);
			switch (sym.token) {
			case PP_NEWLINE:
			case PP_WHITESPACE:
				if (last != PP_WHITESPACE) {
					secondlast = last;
					last = PP_WHITESPACE;
					output += ' ';
				}
				continue;
			case PP_STRING_LITERAL:
				if (last == PP_STRING_LITERAL)
					container_chop (output, 1);
				else if (secondlast == PP_STRING_LITERAL && last == PP_WHITESPACE)
					container_chop (output, 2);
				else
					break;
				output += sym.lexem ().substr (1);
				secondlast = last;
				last = PP_STRING_LITERAL;
				continue;
			case LOO_INCLUDE_BEGIN:
				lineNum = 0;
				continue;
			case LOO_INCLUDE_END:
				lineNum = sym.lineNum;
				continue;
			default:
				break;
			}
			secondlast = last;
			last = sym.token;

			const int padding = sym.lineNum - lineNum;
			if (padding > 0) {
				output.resize (output.size () + padding);
				memset (&output[0] + output.size () - padding, '\n', padding);
				lineNum = sym.lineNum;
			}

			output += sym.lexem ();
		}

		return output;
	}

	static LooStringList argumentsFromCommandLineAndFile (const LooStringList &arguments)
	{
		LooStringList allArguments;
		allArguments.reserve (arguments.size ());
		for (const std::string &argument : arguments) {
			// "@file" doesn't start with a '-' so we can't use LooCommandLineParser for it
			//如果以@开头,就是文件
			if(string_startwith(argument,'@')){
			//if (argument.startsWith ('@')) {
				std::string optionsFile = argument;
				optionsFile.erase (0, 1);//去掉@
				if (optionsFile.empty ()) {
					error ("The @ option requires an input file");
					return LooStringList ();
				}
				fs::ifstream f (optionsFile,std::ios::in);//QIODevice::ReadOnly | QIODevice::Text
				if (!f.is_open ())
				{
					error ("Cannot open options file specified with @");
					return LooStringList ();
				}
				//读取文件配置行
				while (!f.eof ()) {
					std::string line;
					std::getline (f, line);
					if (!line.empty ())
						allArguments << line;
				}
			}
			else {
				allArguments << argument;
			}
		}
		return allArguments;
	}

	int runMoc (int argc, char **argv)
	{
		g_LooArguments.Init (argc, argv);
		bool autoInclude = true;
		bool defaultInclude = true;
		Preprocessor pp;
		LooReflect moc;
		pp.macros["LOO_REFLECT_RUN"];
		pp.macros["__cplusplus"];

		// Don't stumble over GCC extensions
		Macro dummyVariadicFunctionMacro;
		dummyVariadicFunctionMacro.isFunction = true;
		dummyVariadicFunctionMacro.isVariadic = true;
		dummyVariadicFunctionMacro.arguments.push_back (Symbol (0, PP_IDENTIFIER, "__VA_ARGS__"));
		pp.macros["__attribute__"] = dummyVariadicFunctionMacro;
		pp.macros["__declspec"] = dummyVariadicFunctionMacro;

		std::string filename;
		std::string output;
		std::istream* in;
		std::ifstream infile;
		FILE *out = 0;

		// Note that moc isn't translated.
		// If you use this code as an example for a translated app, make sure to translate the strings.
		LooCommandLineParser parser;
		parser.setApplicationDescription ("Loo Meta Object Compiler version 1.0.0 (Loo 1.0.0)");
		parser.addHelpOption ();
		parser.addVersionOption ();
		parser.setSingleDashWordOptionMode (LooCommandLineParser::ParseAsLongOptions);//设置了-开头参数的解析

		//-o 输出文件
		LooCommandLineOption outputOption ("o");
		outputOption.setDescription (("Write output to file rather than stdout."));
		outputOption.setValueName (("file"));
		outputOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (outputOption);

		//-I 输入
		LooCommandLineOption includePathOption (("I"));
		includePathOption.setDescription (("Add dir to the include path for header files."));
		includePathOption.setValueName (("dir"));
		includePathOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (includePathOption);

		//-F mac framework
		LooCommandLineOption macFrameworkOption (("F"));
		macFrameworkOption.setDescription (("Add Mac framework to the include path for header files."));
		macFrameworkOption.setValueName (("framework"));
		macFrameworkOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (macFrameworkOption);

		//-E preprocess only
		LooCommandLineOption preprocessOption ( ("E"));
		preprocessOption.setDescription ( ("Preprocess only; do not generate meta object code."));
		parser.addOption (preprocessOption);

		//-D 定义
		LooCommandLineOption defineOption ( ("D"));
		defineOption.setDescription (("Define macro, with optional definition."));
		defineOption.setValueName (("macro[=def]"));
		defineOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (defineOption);

		//-D 不定义
		LooCommandLineOption undefineOption ( ("U"));
		undefineOption.setDescription (("Undefine macro."));
		undefineOption.setValueName (("macro"));
		undefineOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (undefineOption);

		//-M 插件数据
		LooCommandLineOption metadataOption (("M"));
		metadataOption.setDescription (("Add key/value pair to plugin meta data"));
		metadataOption.setValueName (("key=value"));
		metadataOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (metadataOption);

		//
		LooCommandLineOption compilerFlavorOption (("compiler-flavor"));
		compilerFlavorOption.setDescription (("Set the compiler flavor: either \"msvc\" or \"unix\"."));
		compilerFlavorOption.setValueName (("flavor"));
		parser.addOption (compilerFlavorOption);

		//i
		LooCommandLineOption noIncludeOption ( ("i"));
		noIncludeOption.setDescription ( ("Do not generate an #include statement."));
		parser.addOption (noIncludeOption);

		LooCommandLineOption pathPrefixOption ( ("p"));
		pathPrefixOption.setDescription ( ("Path prefix for included file."));
		pathPrefixOption.setValueName ( ("path"));
		pathPrefixOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (pathPrefixOption);

		LooCommandLineOption forceIncludeOption ( ("f"));
		forceIncludeOption.setDescription ( ("Force #include <file> (overwrite default)."));
		forceIncludeOption.setValueName ( ("file"));
		forceIncludeOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (forceIncludeOption);

		LooCommandLineOption prependIncludeOption ( ("b"));
		prependIncludeOption.setDescription ( ("Prepend #include <file> (preserve default include)."));
		prependIncludeOption.setValueName ( ("file"));
		prependIncludeOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (prependIncludeOption);

		LooCommandLineOption includeOption ( ("include"));
		includeOption.setDescription ( ("Parse <file> as an #include before the main source(s)."));
		includeOption.setValueName ( ("file"));
		parser.addOption (includeOption);

		LooCommandLineOption noNotesWarningsCompatOption ( ("n"));
		noNotesWarningsCompatOption.setDescription ( ("Do not display notes (-nn) or warnings (-nw). Compatibility option."));
		noNotesWarningsCompatOption.setValueName ( ("which"));
		noNotesWarningsCompatOption.setFlags (LooCommandLineOption::ShortOptionStyle);
		parser.addOption (noNotesWarningsCompatOption);

		LooCommandLineOption noNotesOption ( ("no-notes"));
		noNotesOption.setDescription ( ("Do not display notes."));
		parser.addOption (noNotesOption);

		LooCommandLineOption noWarningsOption ( ("no-warnings"));
		noWarningsOption.setDescription ( ("Do not display warnings (implies --no-notes)."));
		parser.addOption (noWarningsOption);

		LooCommandLineOption ignoreConflictsOption ( ("ignore-option-clashes"));
		ignoreConflictsOption.setDescription ( ("Ignore all options that conflict with compilers, like -pthread conflicting with moc's -p option."));
		parser.addOption (ignoreConflictsOption);

		parser.addPositionalArgument ( ("[header-file]"),
			 ("Header file to read from, otherwise stdin."));
		parser.addPositionalArgument ( ("[@option-file]"),
			 ("Read additional options from option-file."));

		//根据参数简介索引文件读取完整配置信息
		const LooStringList arguments = argumentsFromCommandLineAndFile (g_LooArguments.arguments ());
		if (arguments.empty ())
			return 1;

		//分析输入的命令参数,解析得到配置参数
		parser.process (arguments);

		const LooStringList files = parser.positionalArguments ();
		if (files.size () > 1) {
			error (( std::string("Too many input files specified: '") + files.join ( ("' '")) +  ('\'')).c_str());
			parser.showHelp (1);
		}
		else if (!files.empty ()) {
			filename = *files.begin ();
		}

		const bool ignoreConflictingOptions = parser.isSet (ignoreConflictsOption);
		output = parser.value (outputOption);
		pp.preprocessOnly = parser.isSet (preprocessOption);
		if (parser.isSet (noIncludeOption)) {
			moc.noInclude = true;
			autoInclude = false;
		}
		if (!ignoreConflictingOptions) {
			if (parser.isSet (forceIncludeOption)) {
				moc.noInclude = false;
				autoInclude = false;
				const auto forceIncludes = parser.values (forceIncludeOption);
				for (const std::string &include : forceIncludes) {
					moc.includeFiles.push_back ((include));
					defaultInclude = false;
				}
			}
			const auto prependIncludes = parser.values (prependIncludeOption);
			for (const std::string &include : prependIncludes)
				moc.includeFiles.insert (moc.includeFiles .begin(),(include));
			if (parser.isSet (pathPrefixOption))
				moc.includePath = (parser.value (pathPrefixOption));
		}

		const auto includePaths = parser.values (includePathOption);
		for (const std::string &path : includePaths)
			pp.includes.push_back(Preprocessor::IncludePath ((path)));
		std::string compilerFlavor = parser.value (compilerFlavorOption);
		if (compilerFlavor.empty () || compilerFlavor ==  ("unix")) {
			// traditional Unix compilers use both CPATH and CPLUS_INCLUDE_PATH
			// $CPATH feeds to #include <...> and #include "...", whereas
			// CPLUS_INCLUDE_PATH is equivalent to GCC's -isystem, so we parse later
			const auto cpath = string_split(qgetenv ("CPATH"),fs::path::preferred_separator);
			for (const QByteArray &p : cpath)
				pp.includes.push_back( Preprocessor::IncludePath (p));
			const auto cplus_include_path = string_split (qgetenv ("CPLUS_INCLUDE_PATH"), fs::path::preferred_separator);
			for (const QByteArray &p : cplus_include_path)
				pp.includes.push_back (Preprocessor::IncludePath (p));
		}
		else if (compilerFlavor ==  ("msvc")) {
			// MSVC uses one environment variable: INCLUDE
			const auto include = string_split (qgetenv ("CPLUS_INCLUDE_PATH"), fs::path::preferred_separator);
			for (const QByteArray &p : include)
				pp.includes.push_back (Preprocessor::IncludePath (p));
		}
		else {
			error ( (std::string ("Unknown compiler flavor '") + compilerFlavor +
				("'; valid values are: msvc, unix.")).c_str());
			parser.showHelp (1);
		}

		const auto macFrameworks = parser.values (macFrameworkOption);
		for (const std::string &path : macFrameworks) {
			// minimalistic framework support for the mac
			Preprocessor::IncludePath p ( (path));
			p.isFrameworkPath = true;
			pp.includes.push_back( p);
		}
		const auto defines = parser.values (defineOption);
		for (const std::string &arg : defines) {
			QByteArray name = arg;
			QByteArray value ("1");
			int eq = name.find_first_of ('=');
			if (eq >= 0) {
				value = name.substr (eq + 1);
				name = string_left (name,eq);
			}
			if (name.empty ()) {
				error ("Missing macro name");
				parser.showHelp (1);
			}
			Macro macro;
			macro.symbols = Preprocessor::tokenize (value, 1, Preprocessor::TokenizeDefine);
			macro.symbols.pop_back (); // remove the EOF symbol
			pp.macros.insert (std::make_pair(name, macro));
		}
		const auto undefines = parser.values (undefineOption);
		for (const std::string &arg : undefines) {
			QByteArray macro = arg;
			if (macro.empty ()) {
				error ("Missing macro name");
				parser.showHelp (1);
			}
			pp.macros.erase (macro);
		}
		const LooStringList noNotesCompatValues = parser.values (noNotesWarningsCompatOption);
		if (parser.isSet (noNotesOption) || std::find (noNotesCompatValues.begin(), noNotesCompatValues.end(), ("n"))!= noNotesCompatValues.end())
			moc.displayNotes = false;
		if (parser.isSet (noWarningsOption) || std::find (noNotesCompatValues.begin (), noNotesCompatValues.end (), ("w"))!= noNotesCompatValues.end())
			moc.displayWarnings = moc.displayNotes = false;

		if (autoInclude) {
			int spos = filename.find_last_of (fs::path::preferred_separator);
			int ppos = filename.find_last_of (('.'));
			// spos >= -1 && ppos > spos => ppos >= 0
			moc.noInclude = (ppos > spos && std::tolower(filename[ppos + 1]) != ('h'));
		}
		if (defaultInclude) {
			if (moc.includePath.empty ()) {
				if (filename.size ()) {
					if (output.size ())
						moc.includeFiles.push_back (combinePath (filename, output));
					else
						moc.includeFiles.push_back ((filename));
				}
			}
			else {
				moc.includeFiles.push_back (combinePath (filename, filename));
			}
		}
		if (filename.empty ()) {
			filename =  ("standard input");	
			in = &(std::cin); 
		}
		else {
			infile = std::ifstream(filename,std::ios::in);
			if (!infile.is_open()) {
				fprintf (stderr, "moc: %s: No such file\n", filename.c_str());
				return 1;
			}
			in = &infile;
			moc.filename = filename;
		}

		const auto metadata = parser.values (metadataOption);
		for (const std::string &md : metadata) {
			int split = md.find_first_of ( ('='));
			std::string key = string_left (md,split);
			std::string value = md.substr (split + 1);

			if (split == -1 || key.empty () || value.empty ()) {
				error ("missing key or value for option '-M'");
			}
			else if (key.find_first_of ( ('.')) != -1) {
				// Don't allow keys with '.' for now, since we might need this
				// format later for more advanced meta data API
				error ("A key cannot contain the letter '.' for option '-M'");
			}
			else {
				nlohmann::json array = moc.metaArgs[key];
				array.push_back (value);
				moc.metaArgs.insert (std::make_pair(key, array));
			}
		}

		moc.currentFilenames.push (filename);
		moc.includes = pp.includes;

		// 1. preprocess
		const auto includeFiles = parser.values (includeOption);
		for (const std::string &includeName : includeFiles) {
			QByteArray rawName = pp.resolveInclude ( (includeName), moc.filename);
			if (rawName.empty ()) {
				fprintf (stderr, "Warning: Failed to resolve include \"%s\" for moc file %s\n",
					includeName.data (),
					moc.filename.empty () ? "<standard input>" : moc.filename.data ());
			}
			else {
				fs::ifstream f ( (rawName));
				if (f.is_open()) {
					moc.symbols.push_back(Symbol (0, LOO_INCLUDE_BEGIN, rawName));
					auto l = pp.preprocessed (rawName, f);
					moc.symbols.insert (moc.symbols.end(),l.begin(),l.end());
					moc.symbols.push_back (Symbol (0, LOO_INCLUDE_END, rawName));
				}
				else {
					fprintf (stderr, "Warning: Cannot open %s included by moc file %s: %d\n",
						rawName.data (),
						moc.filename.empty () ? "<standard input>" : moc.filename.data (),
						f.exceptions);
				}
			}
		}
		auto li = pp.preprocessed (moc.filename, *in);
		moc.symbols.insert(moc.symbols.end(),li.begin(),li.end());

		if (!pp.preprocessOnly) {
			// 2. parse
			moc.parse ();
		}

		// 3. and output meta object code

		if (output.size ()) { // output file specified
#if defined(_MSC_VER)
			std::wstring ws = s2ws (output);
			if (_wfopen_s (&out, ws.c_str (), L"w") != 0)
#else
			out = fopen (QFile::encodeName (output).constData (), "w"); // create output file
			if (!out)
#endif
			{
				fprintf (stderr, "moc: Cannot create %s\n",  (output).data ());
				return 1;
			}
		}
		else { // use stdout
			out = stdout;
		}

		if (pp.preprocessOnly) {
			fprintf (out, "%s\n", composePreprocessorOutput (moc.symbols).data ());
		}
		else {
			if (moc.classList.empty ())
				moc.note ("No relevant classes found. No output generated.");
			else
				moc.generate (out);
		}

		if (output.size ())
			fclose (out);

		return 0;
	}
}

int main (int argc,char** argv)
{
	loo::runMoc (argc, argv);
	return 0;
}