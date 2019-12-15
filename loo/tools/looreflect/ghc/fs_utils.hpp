#ifndef __FS_UTILS_HPP
#define __FS_UTILS_HPP
#include "fs_std.hpp"

namespace fs
{
	//todo debug
	inline std::string  combine_path_file (const fs::path& dir, const fs::path& fileName) {
		if (fileName.is_absolute ())
		{
			return fileName.string();
		}
		fs::directory_entry de (dir);
		std::string ret = de.path().string ();
		if (!fileName.empty ())
		{
			if (!ret.empty () && ret[(int)ret.length () - 1] != '/' && fileName.string()[0] != '/')
			{
				ret += '/';
			}
			ret += fileName.string ();
		}
		return ret;
	}
}

#endif