#include "commandlineparser.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include "utils.h"
#include <assert.h>
#include <algorithm>
#include "looarguments.h"

namespace loo
{
	typedef std::unordered_map<std::string, int> NameHash_t;

	class LooCommandLineParserPrivate
	{
	public:
		inline LooCommandLineParserPrivate ()
			: singleDashWordOptionMode (LooCommandLineParser::ParseAsCompactedShortOptions),
			optionsAfterPositionalArgumentsMode (LooCommandLineParser::ParseAsOptions),
			builtinVersionOption (false),
			builtinHelpOption (false),
			needsParsing (true)
		{ }

		bool parse (const LooStringList &args);
		void checkParsed (const char *method);
		LooStringList aliases (const std::string &name) const;
		std::string helpText () const;
		bool registerFoundOption (const std::string &optionName);
		bool parseOptionValue (const std::string &optionName, const std::string &argument,
			LooStringList::const_iterator *argumentIterator,
			LooStringList::const_iterator argsEnd);

		//! Error text set when parse() returns false
		std::string errorText;

		//! The command line options used for parsing
		std::vector<LooCommandLineOption> commandLineOptionList;

		//! Hash mapping option names to their offsets in commandLineOptionList and optionArgumentList.
		NameHash_t nameHash;

		//! Option values found (only for options with a value)
		std::unordered_map<int, LooStringList> optionValuesHash;

		//! Names of options found on the command line.
		LooStringList optionNames;

		//! Arguments which did not belong to any option.
		LooStringList positionalArgumentList;

		//! Names of options which were unknown.
		LooStringList unknownOptionNames;

		//! Application description
		std::string description;

		//! Documentation for positional arguments
		struct PositionalArgumentDefinition
		{
			std::string name;
			std::string description;
			std::string syntax;
		};
		std::vector<PositionalArgumentDefinition> positionalArgumentDefinitions;

		//! The parsing mode for "-abc"
		LooCommandLineParser::SingleDashWordOptionMode singleDashWordOptionMode;

		//! How to parse "arg -option"
		LooCommandLineParser::OptionsAfterPositionalArgumentsMode optionsAfterPositionalArgumentsMode;

		//! Whether addVersionOption was called
		bool builtinVersionOption;

		//! Whether addHelpOption was called
		bool builtinHelpOption;

		//! True if parse() needs to be called
		bool needsParsing;
	};

	LooStringList LooCommandLineParserPrivate::aliases (const std::string &optionName) const
	{
		const NameHash_t::const_iterator it = nameHash.find (optionName);
		if (it == nameHash.cend ()) {
			printf ("LooCommandLineParser: option not defined: \"%s\"", optionName.c_str());
			return LooStringList ();
		}
		return commandLineOptionList[it->second].names ();
	}

	/*!
		\since 5.2
		\class LooCommandLineParser
		\inmodule QtCore
		\ingroup tools

		\brief The LooCommandLineParser class provides a means for handling the
		command line options.

		QCoreApplication provides the command-line arguments as a simple list of strings.
		LooCommandLineParser provides the ability to define a set of options, parse the
		command-line arguments, and store which options have actually been used, as
		well as option values.

		Any argument that isn't an option (i.e. doesn't start with a \c{-}) is stored
		as a "positional argument".

		The parser handles short names, long names, more than one name for the same
		option, and option values.

		Options on the command line are recognized as starting with a single or
		double \c{-} character(s).
		The option \c{-} (single dash alone) is a special case, often meaning standard
		input, and not treated as an option. The parser will treat everything after the
		option \c{--} (double dash) as positional arguments.

		Short options are single letters. The option \c{v} would be specified by
		passing \c{-v} on the command line. In the default parsing mode, short options
		can be written in a compact form, for instance \c{-abc} is equivalent to \c{-a -b -c}.
		The parsing mode for can be set to ParseAsLongOptions, in which case \c{-abc}
		will be parsed as the long option \c{abc}.

		Long options are more than one letter long and cannot be compacted together.
		The long option \c{verbose} would be passed as \c{--verbose} or \c{-verbose}.

		Passing values to options can be done using the assignment operator: \c{-v=value}
		\c{--verbose=value}, or a space: \c{-v value} \c{--verbose value}, i.e. the next
		argument is used as value (even if it starts with a \c{-}).

		The parser does not support optional values - if an option is set to
		require a value, one must be present. If such an option is placed last
		and has no value, the option will be treated as if it had not been
		specified.

		The parser does not automatically support negating or disabling long options
		by using the format \c{--disable-option} or \c{--no-option}. However, it is
		possible to handle this case explicitly by making an option with \c{no-option}
		as one of its names, and handling the option explicitly.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser_main.cpp 0

		If your compiler supports the C++11 standard, the three addOption() calls in
		the above example can be simplified:
		\snippet code/src_corelib_tools_qcommandlineparser_main.cpp cxx11

		Known limitation: the parsing of Qt options inside QCoreApplication and subclasses
		happens before LooCommandLineParser exists, so it can't take it into account. This
		means any option value that looks like a builtin Qt option, will be treated by
		QCoreApplication as a builtin Qt option. Example: \c{--profile -reverse} will
		lead to QGuiApplication seeing the -reverse option set, and removing it from
		QCoreApplication::arguments() before LooCommandLineParser defines the \c{profile}
		option and parses the command line.

		\section2 How to Use LooCommandLineParser in Complex Applications

		In practice, additional error checking needs to be performed on the positional
		arguments and option values. For example, ranges of numbers should be checked.

		It is then advisable to introduce a function to do the command line parsing
		which takes a struct or class receiving the option values returning an
		enumeration representing the result. The dnslookup example of the QtNetwork
		module illustrates this:

		\snippet dnslookup.h 0

		\snippet dnslookup.cpp 0

		In the main function, help should be printed to the standard output if the help option
		was passed and the application should return the exit code 0.

		If an error was detected, the error message should be printed to the standard
		error output and the application should return an exit code other than 0.

		\snippet dnslookup.cpp 1

		A special case to consider here are GUI applications on Windows and mobile
		platforms. These applications may not use the standard output or error channels
		since the output is either discarded or not accessible.

		On Windows, LooCommandLineParser uses message boxes to display usage information
		and errors if no console window can be obtained.

		For other platforms, it is recommended to display help texts and error messages
		using a QMessageBox. To preserve the formatting of the help text, rich text
		with \c <pre> elements should be used:

		\code

		switch (parseCommandLine(parser, &query, &errorMessage)) {
		case CommandLineOk:
			break;
		case CommandLineError:
			QMessageBox::warning(0, QGuiApplication::applicationDisplayName(),
								 "<html><head/><body><h2>" + errorMessage + "</h2><pre>"
								 + parser.helpText() + "</pre></body></html>");
			return 1;
		case CommandLineVersionRequested:
			QMessageBox::information(0, QGuiApplication::applicationDisplayName(),
									 QGuiApplication::applicationDisplayName() + ' '
									 + QCoreApplication::applicationVersion());
			return 0;
		case CommandLineHelpRequested:
			QMessageBox::warning(0, QGuiApplication::applicationDisplayName(),
								 "<html><head/><body><pre>"
								 + parser.helpText() + "</pre></body></html>");
			return 0;
		}
		\endcode

		However, this does not apply to the dnslookup example, because it is a
		console application.

		\sa LooCommandLineOption, QCoreApplication
	*/

	/*!
		Constructs a command line parser object.
	*/
	LooCommandLineParser::LooCommandLineParser ()
		: d (new LooCommandLineParserPrivate)
	{
	}

	/*!
		Destroys the command line parser object.
	*/
	LooCommandLineParser::~LooCommandLineParser ()
	{
		delete d;
	}

	/*!
		\enum LooCommandLineParser::SingleDashWordOptionMode

		This enum describes the way the parser interprets command-line
		options that use a single dash followed by multiple letters, as as \c{-abc}.

		\value ParseAsCompactedShortOptions \c{-abc} is interpreted as \c{-a -b -c},
		i.e. as three short options that have been compacted on the command-line,
		if none of the options take a value. If \c{a} takes a value, then it
		is interpreted as \c{-a bc}, i.e. the short option \c{a} followed by the value \c{bc}.
		This is typically used in tools that behave like compilers, in order
		to handle options such as \c{-DDEFINE=VALUE} or \c{-I/include/path}.
		This is the default parsing mode. New applications are recommended to
		use this mode.

		\value ParseAsLongOptions \c{-abc} is interpreted as \c{--abc},
		i.e. as the long option named \c{abc}. This is how Qt's own tools
		(uic, rcc...) have always been parsing arguments. This mode should be
		used for preserving compatibility in applications that were parsing
		arguments in such a way. There is an exception if the \c{a} option has the
		LooCommandLineOption::ShortOptionStyle flag set, in which case it is still
		interpreted as \c{-a bc}.

		\sa setSingleDashWordOptionMode()
	*/

	/*!
		Sets the parsing mode to \a singleDashWordOptionMode.
		This must be called before process() or parse().
	*/
	void LooCommandLineParser::setSingleDashWordOptionMode (LooCommandLineParser::SingleDashWordOptionMode singleDashWordOptionMode)
	{
		d->singleDashWordOptionMode = singleDashWordOptionMode;
	}

	/*!
		\enum LooCommandLineParser::OptionsAfterPositionalArgumentsMode

		This enum describes the way the parser interprets options that
		occur after positional arguments.

		\value ParseAsOptions \c{application argument --opt -t} is interpreted as setting
		the options \c{opt} and \c{t}, just like \c{application --opt -t argument} would do.
		This is the default parsing mode. In order to specify that \c{--opt} and \c{-t}
		are positional arguments instead, the user can use \c{--}, as in
		\c{application argument -- --opt -t}.

		\value ParseAsPositionalArguments \c{application argument --opt} is interpreted as
		having two positional arguments, \c{argument} and \c{--opt}.
		This mode is useful for executables that aim to launch other executables
		(e.g. wrappers, debugging tools, etc.) or that support internal commands
		followed by options for the command. \c{argument} is the name of the command,
		and all options occurring after it can be collected and parsed by another
		command line parser, possibly in another executable.

		\sa setOptionsAfterPositionalArgumentsMode()

		\since 5.6
	*/

	/*!
		Sets the parsing mode to \a parsingMode.
		This must be called before process() or parse().
		\since 5.6
	*/
	void LooCommandLineParser::setOptionsAfterPositionalArgumentsMode (LooCommandLineParser::OptionsAfterPositionalArgumentsMode parsingMode)
	{
		d->optionsAfterPositionalArgumentsMode = parsingMode;
	}

	/*!
		Adds the option \a option to look for while parsing.

		Returns \c true if adding the option was successful; otherwise returns \c false.

		Adding the option fails if there is no name attached to the option, or
		the option has a name that clashes with an option name added before.
	 */
	bool LooCommandLineParser::addOption (const LooCommandLineOption &option)
	{
		const LooStringList optionNames = option.names ();

		if (!optionNames.empty ()) {
			for (const std::string &name : optionNames) {
				if (d->nameHash.find (name) != d->nameHash.end())
					return false;
			}

			d->commandLineOptionList.push_back (option);

			const int offset = d->commandLineOptionList.size () - 1;
			for (const std::string &name : optionNames)
				d->nameHash.insert (std::make_pair(name, offset));

			return true;
		}

		return false;
	}

	/*!
		\since 5.4

		Adds the options to look for while parsing. The options are specified by
		the parameter \a options.

		Returns \c true if adding all of the options was successful; otherwise
		returns \c false.

		See the documentation for addOption() for when this function may fail.
	*/
	bool LooCommandLineParser::addOptions (const std::vector<LooCommandLineOption> &options)
	{
		// should be optimized (but it's no worse than what was possible before)
		bool result = true;
		for (std::vector<LooCommandLineOption>::const_iterator it = options.begin (), end = options.end (); it != end; ++it)
			result &= addOption (*it);
		return result;
	}

	/*!
		Adds the \c{-v} / \c{--version} option, which displays the version string of the application.

		This option is handled automatically by LooCommandLineParser.

		You can set the actual version string by using QCoreApplication::setApplicationVersion().

		Returns the option instance, which can be used to call isSet().
	*/
	LooCommandLineOption LooCommandLineParser::addVersionOption ()
	{
		LooCommandLineOption opt (LooStringList () << "v" << "version", "Displays version information.");
		addOption (opt);
		d->builtinVersionOption = true;
		return opt;
	}

	/*!
		Adds the help option (\c{-h}, \c{--help} and \c{-?} on Windows)
		This option is handled automatically by LooCommandLineParser.

		Remember to use setApplicationDescription to set the application description,
		which will be displayed when this option is used.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser_main.cpp 0

		Returns the option instance, which can be used to call isSet().
	*/
	LooCommandLineOption LooCommandLineParser::addHelpOption ()
	{
		LooCommandLineOption opt (LooStringList ()
#if defined(_MSC_VER)
			<< "?"
#endif
			<< "h"
			<< "help", "Displays this help.");
		addOption (opt);
		d->builtinHelpOption = true;
		return opt;
	}

	/*!
		Sets the application \a description shown by helpText().
	*/
	void LooCommandLineParser::setApplicationDescription (const std::string &description)
	{
		d->description = description;
	}

	/*!
		Returns the application description set in setApplicationDescription().
	*/
	std::string LooCommandLineParser::applicationDescription () const
	{
		return d->description;
	}

	/*!
		Defines an additional argument to the application, for the benefit of the help text.

		The argument \a name and \a description will appear under the \c{Arguments:} section
		of the help. If \a syntax is specified, it will be appended to the Usage line, otherwise
		the \a name will be appended.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser.cpp 2

		\sa addHelpOption(), helpText()
	*/
	void LooCommandLineParser::addPositionalArgument (const std::string &name, const std::string &description, const std::string &syntax)
	{
		LooCommandLineParserPrivate::PositionalArgumentDefinition arg;
		arg.name = name;
		arg.description = description;
		arg.syntax = syntax.empty () ? name : syntax;
		d->positionalArgumentDefinitions.push_back (arg);
	}

	/*!
		Clears the definitions of additional arguments from the help text.

		This is only needed for the special case of tools which support multiple commands
		with different options. Once the actual command has been identified, the options
		for this command can be defined, and the help text for the command can be adjusted
		accordingly.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser.cpp 3
	*/
	void LooCommandLineParser::clearPositionalArguments ()
	{
		d->positionalArgumentDefinitions.clear ();
	}

	/*!
		Parses the command line \a arguments.

		Most programs don't need to call this, a simple call to process() is enough.

		parse() is more low-level, and only does the parsing. The application will have to
		take care of the error handling, using errorText() if parse() returns \c false.
		This can be useful for instance to show a graphical error message in graphical programs.

		Calling parse() instead of process() can also be useful in order to ignore unknown
		options temporarily, because more option definitions will be provided later on
		(depending on one of the arguments), before calling process().

		Don't forget that \a arguments must start with the name of the executable (ignored, though).

		Returns \c false in case of a parse error (unknown option or missing value); returns \c true otherwise.

		\sa process()
	*/
	bool LooCommandLineParser::parse (const LooStringList &arguments)
	{
		return d->parse (arguments);
	}

	/*!
		Returns a translated error text for the user.
		This should only be called when parse() returns \c false.
	*/
	std::string LooCommandLineParser::errorText () const
	{
		if (!d->errorText.empty ())
			return d->errorText;
		if (d->unknownOptionNames.size () == 1)
			return std::string("Unknown option " ) + *d->unknownOptionNames.begin ();
		if (d->unknownOptionNames.size () > 1)
			return std::string ("Unknown options: %1.") + (d->unknownOptionNames.join (", "));
		return std::string ();
	}

	enum MessageType { UsageMessage, ErrorMessage };

	static void showParserMessage (const std::string &message, MessageType type)
	{
		fputs (message.c_str(), type == UsageMessage ? stdout : stderr);
	}

	/*!
		Processes the command line \a arguments.

		In addition to parsing the options (like parse()), this function also handles the builtin
		options and handles errors.

		The builtin options are \c{--version} if addVersionOption was called and \c{--help} if addHelpOption was called.

		When invoking one of these options, or when an error happens (for instance an unknown option was
		passed), the current process will then stop, using the exit() function.

		\sa QCoreApplication::arguments(), parse()
	 */
	void LooCommandLineParser::process (const LooStringList &arguments)
	{
		if (!d->parse (arguments)) {
			showParserMessage (errorText () + '\n', ErrorMessage);
			//loo_call_post_routines ();
			::exit (EXIT_FAILURE);
		}

		if (d->builtinVersionOption && isSet ("version"))
			showVersion ();

		if (d->builtinHelpOption && isSet ("help"))
			showHelp (EXIT_SUCCESS);
	}

	void LooCommandLineParserPrivate::checkParsed (const char *method)
	{
		if (needsParsing)
			printf ("LooCommandLineParser: call process() or parse() before %s", method);
	}

	/*!
		\internal
		Looks up the option \a optionName (found on the command line) and register it as found.
		Returns \c true on success.
	 */
	bool LooCommandLineParserPrivate::registerFoundOption (const std::string &optionName)
	{
		if (nameHash.find (optionName) != nameHash.end()) {
			optionNames.append (optionName);
			return true;
		}
		else {
			unknownOptionNames.append (optionName);
			return false;
		}
	}

	/*!
		\internal
		\brief Parse the value for a given option, if it was defined to expect one.

		The value is taken from the next argument, or after the equal sign in \a argument.

		\param optionName the short option name
		\param argument the argument from the command line currently parsed. Only used for -k=value parsing.
		\param argumentIterator iterator to the currently parsed argument. Incremented if the next argument contains the value.
		\param argsEnd args.end(), to check if ++argumentIterator goes out of bounds
		Returns \c true on success.
	 */
	bool LooCommandLineParserPrivate::parseOptionValue (const std::string &optionName, const std::string &argument,
		LooStringList::const_iterator *argumentIterator, LooStringList::const_iterator argsEnd)
	{
		const char assignChar = ('=');
		const NameHash_t::const_iterator nameHashIt = nameHash.find (optionName);
		if (nameHashIt != nameHash.end ()) {
			const int assignPos = argument.find_first_of (assignChar);
			const NameHash_t::mapped_type optionOffset = nameHashIt->second;
			const bool withValue = !commandLineOptionList.at (optionOffset).valueName ().empty ();
			if (withValue) {
				if (assignPos == -1) {
					++(*argumentIterator);
					if (*argumentIterator == argsEnd) {
						errorText = std::string("Missing value after ") + (argument);
						return false;
					}
					optionValuesHash[optionOffset].append (*(*argumentIterator));
				}
				else {
					optionValuesHash[optionOffset].append (argument.substr (assignPos + 1));
				}
			}
			else {
				if (assignPos != -1) {
					errorText =std::string ("Unexpected value after ") + (string_left (argument,assignPos));
					return false;
				}
			}
		}
		return true;
	}

	/*!
		\internal

		Parse the list of arguments \a args, and fills in
		optionNames, optionValuesHash, unknownOptionNames, positionalArguments, and errorText.

		Any results from a previous parse operation are removed.

		The parser will not look for further options once it encounters the option
		\c{--}; this does not include when \c{--} follows an option that requires a value.
	 */
	bool LooCommandLineParserPrivate::parse (const LooStringList &args)
	{
		needsParsing = false;
		bool error = false;

		const std::string     doubleDashString ("--");
		const char dashChar = ('-');
		const char assignChar = ('=');

		bool forcePositional = false;
		errorText.clear ();
		positionalArgumentList.clear ();
		optionNames.clear ();
		unknownOptionNames.clear ();
		optionValuesHash.clear ();

		if (args.empty ()) {
			lWarning ("LooCommandLineParser: argument list cannot be empty, it should contain at least the executable name");
			return false;
		}

		LooStringList::const_iterator argumentIterator = args.begin ();
		++argumentIterator; // skip executable name

		for (; argumentIterator != args.end (); ++argumentIterator) {
			std::string argument = *argumentIterator;

			if (forcePositional) {
				positionalArgumentList.append (argument);
			}
			else if (string_startwith (argument,doubleDashString)) {
				if (argument.length () > 2) {
					std::string optionName = string_section(argument.substr (2),assignChar, 0, 0);
					if (registerFoundOption (optionName)) {
						if (!parseOptionValue (optionName, argument, &argumentIterator, args.end ()))
							error = true;
					}
					else {
						error = true;
					}
				}
				else {
					forcePositional = true;
				}
			}
			else if (string_startwith (argument,dashChar)) {
				if (argument.size () == 1) { // single dash ("stdin")
					positionalArgumentList.append (argument);
					continue;
				}
				switch (singleDashWordOptionMode) {
				case LooCommandLineParser::ParseAsCompactedShortOptions:
				{
					std::string optionName;
					bool valueFound = false;
					for (int pos = 1; pos < argument.size (); ++pos) {
						optionName = argument.substr (pos, 1);
						if (!registerFoundOption (optionName)) {
							error = true;
						}
						else {
							const NameHash_t::const_iterator nameHashIt = nameHash.find (optionName);
							assert (nameHashIt != nameHash.end ()); // checked by registerFoundOption
							const NameHash_t::mapped_type optionOffset = nameHashIt->second;
							const bool withValue = !commandLineOptionList.at (optionOffset).valueName ().empty ();
							if (withValue) {
								if (pos + 1 < argument.size ()) {
									if (argument.at (pos + 1) == assignChar)
										++pos;
									optionValuesHash[optionOffset].append (argument.substr (pos + 1));
									valueFound = true;
								}
								break;
							}
							if (pos + 1 < argument.size () && argument.at (pos + 1) == assignChar)
								break;
						}
					}
					if (!valueFound && !parseOptionValue (optionName, argument, &argumentIterator, args.end ()))
						error = true;
					break;
				}
				case LooCommandLineParser::ParseAsLongOptions:
				{
					if (argument.size () > 2) {
						const std::string possibleShortOptionStyleName = argument.substr (1, 1);
						const auto shortOptionIt = nameHash.find (possibleShortOptionStyleName);
						if (shortOptionIt != nameHash.end ()) {
							const auto &arg = commandLineOptionList[shortOptionIt->second];
							if (arg.flags () & LooCommandLineOption::ShortOptionStyle) {
								registerFoundOption (possibleShortOptionStyleName);
								optionValuesHash[shortOptionIt->second].append (argument.substr (2));
								break;
							}
						}
					}
					const std::string optionName =string_section(argument.substr (1), assignChar, 0, 0);
					if (registerFoundOption (optionName)) {
						if (!parseOptionValue (optionName, argument, &argumentIterator, args.end ()))
							error = true;
					}
					else {
						error = true;
					}
					break;
				}
				}
			}
			else {
				positionalArgumentList.append (argument);
				if (optionsAfterPositionalArgumentsMode == LooCommandLineParser::ParseAsPositionalArguments)
					forcePositional = true;
			}
			if (argumentIterator == args.end ())
				break;
		}
		return !error;
	}

	/*!
		Checks whether the option \a name was passed to the application.

		Returns \c true if the option \a name was set, false otherwise.

		The name provided can be any long or short name of any option that was
		added with \c addOption(). All the options names are treated as being
		equivalent. If the name is not recognized or that option was not present,
		false is returned.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser.cpp 0
	 */

	bool LooCommandLineParser::isSet (const std::string &name) const
	{
		d->checkParsed ("isSet");
		if (d->optionNames.contains (name))
			return true;
		const LooStringList aliases = d->aliases (name);
		for (const std::string &optionName : std::as_const (d->optionNames)) {
			if (std::find(aliases.begin(), aliases.end(),optionName)!= aliases.end())
				return true;
		}
		return false;
	}

	/*!
		Returns the option value found for the given option name \a optionName, or
		an empty string if not found.

		The name provided can be any long or short name of any option that was
		added with \c addOption(). All the option names are treated as being
		equivalent. If the name is not recognized or that option was not present, an
		empty string is returned.

		For options found by the parser, the last value found for
		that option is returned. If the option wasn't specified on the command line,
		the default value is returned.

		An empty string is returned if the option does not take a value.

		\sa values(), LooCommandLineOption::setDefaultValue(), LooCommandLineOption::setDefaultValues()
	 */

	std::string LooCommandLineParser::value (const std::string &optionName) const
	{
		d->checkParsed ("value");
		const LooStringList valueList = values (optionName);

		if (!valueList.empty ())
			return valueList[valueList.size() - 1];

		return std::string ();
	}

	/*!
		Returns a list of option values found for the given option name \a
		optionName, or an empty list if not found.

		The name provided can be any long or short name of any option that was
		added with \c addOption(). All the options names are treated as being
		equivalent. If the name is not recognized or that option was not present, an
		empty list is returned.

		For options found by the parser, the list will contain an entry for
		each time the option was encountered by the parser. If the option wasn't
		specified on the command line, the default values are returned.

		An empty list is returned if the option does not take a value.

		\sa value(), LooCommandLineOption::setDefaultValue(), LooCommandLineOption::setDefaultValues()
	 */

	LooStringList LooCommandLineParser::values (const std::string &optionName) const
	{
		d->checkParsed ("values");
		const NameHash_t::const_iterator it = d->nameHash.find (optionName);
		if (it != d->nameHash.cend ()) {
			const int optionOffset = it->second;
			LooStringList values = d->optionValuesHash.find (optionOffset)->second;
			if (values.empty ())
				values = d->commandLineOptionList.at (optionOffset).defaultValues ();
			return values;
		}

		printf ("LooCommandLineParser: option not defined: \"%s\"", (optionName.c_str()));
		return LooStringList ();
	}

	/*!
		\overload
		Checks whether the \a option was passed to the application.

		Returns \c true if the \a option was set, false otherwise.

		This is the recommended way to check for options with no values.

		Example:
		\snippet code/src_corelib_tools_qcommandlineparser.cpp 1
	*/
	bool LooCommandLineParser::isSet (const LooCommandLineOption &option) const
	{
		// option.names() might be empty if the constructor failed
		const auto names = option.names ();
		return !names.empty () && isSet (*names.begin ());
	}

	/*!
		\overload
		Returns the option value found for the given \a option, or
		an empty string if not found.

		For options found by the parser, the last value found for
		that option is returned. If the option wasn't specified on the command line,
		the default value is returned.

		An empty string is returned if the option does not take a value.

		\sa values(), LooCommandLineOption::setDefaultValue(), LooCommandLineOption::setDefaultValues()
	*/
	std::string LooCommandLineParser::value (const LooCommandLineOption &option) const
	{
		return value (*option.names ().begin ());
	}

	/*!
		\overload
		Returns a list of option values found for the given \a option,
		or an empty list if not found.

		For options found by the parser, the list will contain an entry for
		each time the option was encountered by the parser. If the option wasn't
		specified on the command line, the default values are returned.

		An empty list is returned if the option does not take a value.

		\sa value(), LooCommandLineOption::setDefaultValue(), LooCommandLineOption::setDefaultValues()
	*/
	LooStringList LooCommandLineParser::values (const LooCommandLineOption &option) const
	{
		return values (*option.names ().begin ());
	}

	/*!
		Returns a list of positional arguments.

		These are all of the arguments that were not recognized as part of an
		option.
	 */

	LooStringList LooCommandLineParser::positionalArguments () const
	{
		d->checkParsed ("positionalArguments");
		return d->positionalArgumentList;
	}

	/*!
		Returns a list of option names that were found.

		This returns a list of all the recognized option names found by the
		parser, in the order in which they were found. For any long options
		that were in the form {--option=value}, the value part will have been
		dropped.

		The names in this list do not include the preceding dash characters.
		Names may appear more than once in this list if they were encountered
		more than once by the parser.

		Any entry in the list can be used with \c value() or with
		\c values() to get any relevant option values.
	 */

	LooStringList LooCommandLineParser::optionNames () const
	{
		d->checkParsed ("optionNames");
		return d->optionNames;
	}

	/*!
		Returns a list of unknown option names.

		This list will include both long an short name options that were not
		recognized. For any long options that were in the form {--option=value},
		the value part will have been dropped and only the long name is added.

		The names in this list do not include the preceding dash characters.
		Names may appear more than once in this list if they were encountered
		more than once by the parser.

		\sa optionNames()
	 */

	LooStringList LooCommandLineParser::unknownOptionNames () const
	{
		d->checkParsed ("unknownOptionNames");
		return d->unknownOptionNames;
	}

	/*!
		Displays the version information from QCoreApplication::applicationVersion(),
		and exits the application.
		This is automatically triggered by the --version option, but can also
		be used to display the version when not using process().
		The exit code is set to EXIT_SUCCESS (0).

		\sa addVersionOption()
		\since 5.4
	*/
	void LooCommandLineParser::showVersion ()
	{
		showParserMessage ("1.0.0",
			UsageMessage);
		//loo_call_post_routines ();
		::exit (EXIT_SUCCESS);
	}

	/*!
		Displays the help information, and exits the application.
		This is automatically triggered by the --help option, but can also
		be used to display the help when the user is not invoking the
		application correctly.
		The exit code is set to \a exitCode. It should be set to 0 if the
		user requested to see the help, and to any other value in case of
		an error.

		\sa helpText()
	*/
	void LooCommandLineParser::showHelp (int exitCode)
	{
		showParserMessage (d->helpText (), UsageMessage);
		//qt_call_post_routines ();
		::exit (exitCode);
	}

	/*!
		Returns a string containing the complete help information.

		\sa showHelp()
	*/
	std::string LooCommandLineParser::helpText () const
	{
		return d->helpText ();
	}

	static std::string wrapText (const std::string &names, int longestOptionNameString, const std::string &description)
	{
		const char nl ('\n');
		std::string text =  ("  ") + string_leftJustified (names,longestOptionNameString) + char (' ');
		const int indent = text.length ();
		int lineStart = 0;
		int lastBreakable = -1;
		const int max = 79 - indent;
		int x = 0;
		const int len = description.length ();

		for (int i = 0; i < len; ++i) {
			++x;
			const char c = description.at (i);
			if (char_isspace (c))
				lastBreakable = i;

			int breakAt = -1;
			int nextLineStart = -1;
			if (x > max && lastBreakable != -1) {
				// time to break and we know where
				breakAt = lastBreakable;
				nextLineStart = lastBreakable + 1;
			}
			else if ((x > max - 1 && lastBreakable == -1) || i == len - 1) {
				// time to break but found nowhere [-> break here], or end of last line
				breakAt = i + 1;
				nextLineStart = breakAt;
			}
			else if (c == nl) {
				// forced break
				breakAt = i;
				nextLineStart = i + 1;
			}

			if (breakAt != -1) {
				const int numChars = breakAt - lineStart;
				//qDebug() << "breakAt=" << description.at(breakAt) << "breakAtSpace=" << breakAtSpace << lineStart << "to" << breakAt << description.substr(lineStart, numChars);
				if (lineStart > 0)
					text += std::string (indent, char (' '));
				text += description.substr (lineStart, numChars) + nl;
				x = 0;
				lastBreakable = -1;
				lineStart = nextLineStart;
				if (lineStart < len && char_isspace (description[lineStart]))
					++lineStart; // don't start a line with a space
				i = lineStart;
			}
		}

		return text;
	}

	std::string LooCommandLineParserPrivate::helpText () const
	{
		const char nl ('\n');
		std::string text;
		std::string usage;
		usage += *g_LooArguments.arguments ().begin (); // executable name
		if (!commandLineOptionList.empty ())
			usage += char (' ') +("[options]");
		for (const PositionalArgumentDefinition &arg : positionalArgumentDefinitions)
			usage += char (' ') + arg.syntax;
		text += std::string("Usage: ") + usage + nl;
		if (!description.empty ())
			text += description + nl;
		text += nl;
		if (!commandLineOptionList.empty ())
			text += ("Options:") + nl;
		LooStringList optionNameList;
		optionNameList.reserve (commandLineOptionList.size ());
		int longestOptionNameString = 0;
		for (const LooCommandLineOption &option : commandLineOptionList) {
			if (option.flags () & LooCommandLineOption::HiddenFromHelp)
				continue;
			const LooStringList optionNames = option.names ();
			std::string optionNamesString;
			for (const std::string &optionName : optionNames) {
				const int numDashes = optionName.length () == 1 ? 1 : 2;
				optionNamesString += std::string("--") + std::to_string(numDashes) + optionName + std::string(", ");
			}
			if (!optionNames.empty ())
				container_chop (optionNamesString,2); // remove trailing ", "
			const auto valueName = option.valueName ();
			if (!valueName.empty ())
				optionNamesString += " <" + valueName + char ('>');
			optionNameList.append (optionNamesString);
			longestOptionNameString = std::max (longestOptionNameString,(int) optionNamesString.length ());
		}
		++longestOptionNameString;
		auto optionNameIterator = optionNameList.cbegin ();
		for (const LooCommandLineOption &option : commandLineOptionList) {
			if (option.flags () & LooCommandLineOption::HiddenFromHelp)
				continue;
			text += wrapText (*optionNameIterator, longestOptionNameString, option.description ());
			++optionNameIterator;
		}
		if (!positionalArgumentDefinitions.empty ()) {
			if (!commandLineOptionList.empty ())
				text += nl;
			text +=  ("Arguments:") + nl;
			for (const PositionalArgumentDefinition &arg : positionalArgumentDefinitions)
				text += wrapText (arg.name, longestOptionNameString, arg.description);
		}
		return text;
	}


}