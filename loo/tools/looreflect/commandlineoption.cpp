#include "commandlineoption.h"
#include <set>
#include "utils.h"

namespace loo
{
	class LooCommandLineOptionPrivate
	{
	public:
		explicit LooCommandLineOptionPrivate (const std::string &name)
			: names (removeInvalidNames (LooStringList (name)))
		{ }

		explicit LooCommandLineOptionPrivate (const LooStringList &names)
			: names (removeInvalidNames (names))
		{ }

		static LooStringList removeInvalidNames (LooStringList nameList);

		//! The list of names used for this option.
		LooStringList names;

		//! The documentation name for the value, if one is expected
		//! Example: "-o <file>" means valueName == "file"
		std::string valueName;

		//! The description used for this option.
		std::string description;

		//! The list of default values used for this option.
		LooStringList defaultValues;

		LooCommandLineOption::Flags flags;
	};

	LooCommandLineOption::LooCommandLineOption (const std::string &name)
		: d (new LooCommandLineOptionPrivate (name))
	{
	}

	/*!
		Constructs a command line option object with the names \a names.

		This overload allows to set multiple names for the option, for instance
		\c{o} and \c{output}.

		The names can be either short or long. Any name in the list that is one
		character in length is a short name. Option names must not be empty,
		must not start with a dash or a slash character, must not contain a \c{=}
		and cannot be repeated.

		\sa setDescription(), setValueName(), setDefaultValues()
	*/
	LooCommandLineOption::LooCommandLineOption (const LooStringList &names)
		: d (new LooCommandLineOptionPrivate (names))
	{
	}

	/*!
		Constructs a command line option object with the given arguments.

		The name of the option is set to \a name.
		The name can be either short or long. If the name is one character in
		length, it is considered a short name. Option names must not be empty,
		must not start with a dash or a slash character, must not contain a \c{=}
		and cannot be repeated.

		The description is set to \a description. It is customary to add a "."
		at the end of the description.

		In addition, the \a valueName needs to be set if the option expects a value.
		The default value for the option is set to \a defaultValue.

		In Qt versions before 5.4, this constructor was \c explicit. In Qt 5.4
		and later, it no longer is and can be used for C++11-style uniform
		initialization:

		\snippet code/src_corelib_tools_qcommandlineoption.cpp cxx11-init

		\sa setDescription(), setValueName(), setDefaultValues()
	*/
	LooCommandLineOption::LooCommandLineOption (const std::string &name, const std::string &description,
		const std::string &valueName,
		const std::string &defaultValue)
		: d (new LooCommandLineOptionPrivate (name))
	{
		setValueName (valueName);
		setDescription (description);
		setDefaultValue (defaultValue);
	}

	/*!
		Constructs a command line option object with the given arguments.

		This overload allows to set multiple names for the option, for instance
		\c{o} and \c{output}.

		The names of the option are set to \a names.
		The names can be either short or long. Any name in the list that is one
		character in length is a short name. Option names must not be empty,
		must not start with a dash or a slash character, must not contain a \c{=}
		and cannot be repeated.

		The description is set to \a description. It is customary to add a "."
		at the end of the description.

		In addition, the \a valueName needs to be set if the option expects a value.
		The default value for the option is set to \a defaultValue.

		In Qt versions before 5.4, this constructor was \c explicit. In Qt 5.4
		and later, it no longer is and can be used for C++11-style uniform
		initialization:

		\snippet code/src_corelib_tools_qcommandlineoption.cpp cxx11-init-list

		\sa setDescription(), setValueName(), setDefaultValues()
	*/
	LooCommandLineOption::LooCommandLineOption (const LooStringList &names, const std::string &description,
		const std::string &valueName,
		const std::string &defaultValue)
		: d (new LooCommandLineOptionPrivate (names))
	{
		setValueName (valueName);
		setDescription (description);
		setDefaultValue (defaultValue);
	}

	/*!
		Constructs a LooCommandLineOption object that is a copy of the LooCommandLineOption
		object \a other.

		\sa operator=()
	*/
	LooCommandLineOption::LooCommandLineOption (const LooCommandLineOption &other)
		: d (other.d)
	{
	}

	/*!
		Destroys the command line option object.
	*/
	LooCommandLineOption::~LooCommandLineOption ()
	{
	}

	/*!
		Makes a copy of the \a other object and assigns it to this LooCommandLineOption
		object.
	*/
	LooCommandLineOption &LooCommandLineOption::operator=(const LooCommandLineOption &other)
	{
		d = other.d;
		return *this;
	}

	/*!
		\fn void LooCommandLineOption::swap(LooCommandLineOption &other)

		Swaps option \a other with this option. This operation is very
		fast and never fails.
	*/

	/*!
		Returns the names set for this option.
	 */
	LooStringList LooCommandLineOption::names () const
	{
		return d->names;
	}

	namespace {
		struct IsInvalidName
		{
			typedef bool result_type;
			typedef std::string argument_type;

			result_type operator()(const std::string &name) const
			{
				if (name.empty ())
				{
					return warn ("be empty");
				}

				const char c = name.at (0);
				if (c == '-')
				{
					return warn ("start with a '-'");
				}
				if (c == '/')
				{
					return warn ("start with a '/'");
				}
				if (c == '=')
				{
					return warn ("contain a '='");
				}
				return false;
			}

			static bool warn (const char *what) 
			{
				lWarning ("LooCommandLineOption: Option names cannot " + std::string(what));
				return true;
			}
		};
	} // unnamed namespace

	// static
	LooStringList LooCommandLineOptionPrivate::removeInvalidNames (LooStringList nameList)
	{
		if(nameList.empty())
			lWarning ("LooCommandLineOption: Options must have at least one name");
		else
			nameList.erase (std::remove_if (nameList.begin (), nameList.end (), IsInvalidName ()),
				nameList.end ());
		return nameList;
	}

	/*!
		Sets the name of the expected value, for the documentation, to \a valueName.

		Options without a value assigned have a boolean-like behavior:
		either the user specifies --option or they don't.

		Options with a value assigned need to set a name for the expected value,
		for the documentation of the option in the help output. An option with names \c{o} and \c{output},
		and a value name of \c{file} will appear as \c{-o, --output <file>}.

		Call QCommandLineParser::value() if you expect the option to be present
		only once, and QCommandLineParser::values() if you expect that option
		to be present multiple times.

		\sa valueName()
	 */
	void LooCommandLineOption::setValueName (const std::string &valueName)
	{
		d->valueName = valueName;
	}

	/*!
		Returns the name of the expected value.

		If empty, the option doesn't take a value.

		\sa setValueName()
	 */
	std::string LooCommandLineOption::valueName () const
	{
		return d->valueName;
	}

	/*!
		Sets the description used for this option to \a description.

		It is customary to add a "." at the end of the description.

		The description is used by QCommandLineParser::showHelp().

		\sa description()
	 */
	void LooCommandLineOption::setDescription (const std::string &description)
	{
		d->description = description;
	}

	/*!
		Returns the description set for this option.

		\sa setDescription()
	 */
	std::string LooCommandLineOption::description () const
	{
		return d->description;
	}

	/*!
		Sets the default value used for this option to \a defaultValue.

		The default value is used if the user of the application does not specify
		the option on the command line.

		If \a defaultValue is empty, the option has no default values.

		\sa defaultValues() setDefaultValues()
	 */
	void LooCommandLineOption::setDefaultValue (const std::string &defaultValue)
	{
		LooStringList newDefaultValues;
		if (!defaultValue.empty ()) {
			newDefaultValues.reserve (1);
			newDefaultValues << defaultValue;
		}
		// commit:
		std::swap (d->defaultValues, newDefaultValues);
	}

	/*!
		Sets the list of default values used for this option to \a defaultValues.

		The default values are used if the user of the application does not specify
		the option on the command line.

		\sa defaultValues() setDefaultValue()
	 */
	void LooCommandLineOption::setDefaultValues (const LooStringList &defaultValues)
	{
		d->defaultValues = defaultValues;
	}

	/*!
		Returns the default values set for this option.

		\sa setDefaultValues()
	 */
	LooStringList LooCommandLineOption::defaultValues () const
	{
		return d->defaultValues;
	}

	/*!
		Returns a set of flags that affect this command-line option.

		\since 5.8
		\sa setFlags(), LooCommandLineOption::Flags
	 */
	LooCommandLineOption::Flags LooCommandLineOption::flags () const
	{
		return d->flags;
	}

	/*!
		Set the set of flags that affect this command-line option to \a flags.

		\since 5.8
		\sa flags(), LooCommandLineOption::Flags
	 */
	void LooCommandLineOption::setFlags (Flags flags)
	{
		d->flags = flags;
	}

}