#ifndef LOOREFLECT_COMMANDLINEOPTION_H
#define LOOREFLECT_COMMANDLINEOPTION_H
#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include "stringlist.h"
namespace loo
{
	class LooCommandLineOptionPrivate;

	class LooCommandLineOption
	{
	public:
		enum Flag {
			HiddenFromHelp = 0x1,
			ShortOptionStyle = 0x2
		};

		typedef std::uint32_t Flags;

		explicit LooCommandLineOption (const std::string &name);
		explicit LooCommandLineOption (const LooStringList &names);
		/*implicit*/ LooCommandLineOption (const std::string &name, const std::string &description,
		const std::string &valueName = std::string (),
		const std::string &defaultValue = std::string ());
		/*implicit*/ LooCommandLineOption (const LooStringList &names, const std::string &description,
		const std::string &valueName = std::string (),
		const std::string &defaultValue = std::string ());
		LooCommandLineOption (const LooCommandLineOption &other);

		~LooCommandLineOption ();

		LooCommandLineOption &operator=(const LooCommandLineOption &other);

		void swap (LooCommandLineOption &other)
		{
			std::swap (d, other.d);
		}

		LooStringList names () const;

		void setValueName (const std::string &name);
		std::string valueName () const;

		void setDescription (const std::string &description);
		std::string description () const;

		void setDefaultValue (const std::string &defaultValue);
		void setDefaultValues (const LooStringList &defaultValues);
		LooStringList defaultValues () const;

		Flags flags () const;
		void setFlags (Flags aflags);

	private:
		std::shared_ptr<LooCommandLineOptionPrivate> d;
	};

}



#endif