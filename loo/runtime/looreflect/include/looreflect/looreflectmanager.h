#ifndef __LOOREFLECT__
#ifndef LOOREFLECTMANAGER_H
#define LOOREFLECTMANAGER_H
#pragma once
#include "dllexport.h"
#include "looreflect/looreflect.h"

namespace looreflect 
{
	namespace detail
	{
		class LooReflectManagerImpl;
	}

	class LOOREFLECT_EXPORT LooReflectManager 
	{
    public:
          typedef std::unordered_map<std::uint64_t, const looreflect::LooType *> T_HASH_TYPE;
		  
	public:
          static LooReflectManager &get();

    public:
          LooReflectManager();
          ~LooReflectManager();

		  void regist_type(const looreflect::LooType *type, const char *moduleName = DEFAULT_MODULE);
		  void remove_type (const char *nsname, const char *moduleName = DEFAULT_MODULE);
		  void remove_type (std::uint64_t hashvalue, const char *moduleName = DEFAULT_MODULE);
		  const looreflect::LooType * get_type(const char *nsname, const char *moduleName = ALL_MODULE); // full name
          const looreflect::LooType *get_type( std::uint64_t hashvalue, const char *moduleName = ALL_MODULE); // full name

		 /* T_HASH_TYPE::const_iterator begin();
          T_HASH_TYPE::const_iterator end();*/
	private:

		detail::LooReflectManagerImpl *m_Impl;
	};
} // namespace looreflect


#endif
#endif