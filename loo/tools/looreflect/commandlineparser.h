#ifndef LOOREFLECT_COMMANDLINEPARSER_H
#define LOOREFLECT_COMMANDLINEPARSER_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include "stringlist.h"
#include "commandlineoption.h"

namespace loo
{
	class LooCommandLineParserPrivate;

	class LooCommandLineParser
	{
		//LOO_DECLARE_TR_FUNCTIONS (LooCommandLineParser)
	public:
		LooCommandLineParser ();
		~LooCommandLineParser ();

		enum SingleDashWordOptionMode {
			ParseAsCompactedShortOptions,
			ParseAsLongOptions
		};
		void setSingleDashWordOptionMode (SingleDashWordOptionMode parsingMode);

		enum OptionsAfterPositionalArgumentsMode {
			ParseAsOptions,
			ParseAsPositionalArguments
		};
		void setOptionsAfterPositionalArgumentsMode (OptionsAfterPositionalArgumentsMode mode);

		bool addOption (const LooCommandLineOption &commandLineOption);
		bool addOptions (const std::vector<LooCommandLineOption> &options);

		LooCommandLineOption addVersionOption ();
		LooCommandLineOption addHelpOption ();
		void setApplicationDescription (const std::string &description);
		std::string applicationDescription () const;
		void addPositionalArgument (const std::string &name, const std::string &description, const std::string &syntax = std::string ());
		void clearPositionalArguments ();

		void process (const LooStringList &arguments);
		//void process (const QCoreApplication &app);

		bool parse (const LooStringList &arguments);
		std::string errorText () const;

		bool isSet (const std::string &name) const;
		std::string value (const std::string &name) const;
		LooStringList values (const std::string &name) const;

		bool isSet (const LooCommandLineOption &option) const;
		std::string value (const LooCommandLineOption &option) const;
		LooStringList values (const LooCommandLineOption &option) const;

		LooStringList positionalArguments () const;
		LooStringList optionNames () const;
		LooStringList unknownOptionNames () const;

		void showVersion ();
		void showHelp (int exitCode = 0);
		std::string helpText () const;

	private:

		LooCommandLineParserPrivate * const d;
	};
}

#endif