#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
#include <mutex>
#include <unordered_map>
#include <shared_mutex>

namespace looreflect 
{
	namespace detail 
	{
		class LooReflectManagerImpl
		{
		public:

			void regist_type (const looreflect::LooType *type, const char *moduleName) {
				std::unique_lock<std::shared_mutex> shareLock (ModulesMutex);
				if (type) {
					m_HashTypeMap[moduleName][type->m_hash] = type;
				}
			}

			void remove_type (std::uint64_t hashvalue, const char *moduleName)
			{
				std::unique_lock<std::shared_mutex> shareLock (ModulesMutex);
				if (strcmp (moduleName, ALL_MODULE) == 0) {
					for (auto it = m_HashTypeMap.begin (); it != m_HashTypeMap.end (); ++it) {
						it->second.erase (hashvalue);
					}
				}
				else {
					auto it = m_HashTypeMap.find (moduleName);
					if (it != m_HashTypeMap.end ()) {
						it->second.erase (hashvalue);
					}
				}
			}

			const looreflect::LooType *get_type (std::uint64_t hashvalue,
				const char *moduleName) {
				std::unique_lock<std::shared_mutex> shareLock (ModulesMutex);
				if (strcmp (moduleName, ALL_MODULE) == 0) {
					for (auto it = m_HashTypeMap.begin (); it != m_HashTypeMap.end (); ++it) {
						auto it_type = it->second.find (hashvalue);
						if (it_type != it->second.end ()) {
							return it_type->second;
						}
					}
				}
				else {
					auto it = m_HashTypeMap.find (moduleName);
					if (it != m_HashTypeMap.end ()) {
						auto it_type = it->second.find (hashvalue);
						if (it_type != it->second.end ()) {
							return it_type->second;
						}
					}
				}
				return nullptr;
			}

		private:
			typedef std::unordered_map<std::uint64_t,  const looreflect::LooType *> T_HashType;
			typedef std::unordered_map<std::string, T_HashType> T_ModelHashType;
			T_ModelHashType m_HashTypeMap;
			std::shared_mutex ModulesMutex;
		};
	}
}

looreflect::LooReflectManager &looreflect::LooReflectManager::get() 
{
  static LooReflectManager *instance = nullptr;
  static std::mutex singleton_mutex_mmgr;
  if (!instance) 
  {
    std::unique_lock<std::mutex> lock(singleton_mutex_mmgr);
    if (!instance) 
	{
      instance = new LooReflectManager();
    }
  }
  return *instance;
}

looreflect::LooReflectManager::LooReflectManager() 
{
  m_Impl = new detail::LooReflectManagerImpl();
}

looreflect::LooReflectManager::~LooReflectManager() 
{ 
	if (m_Impl) 
	{
		delete m_Impl;
		m_Impl = nullptr;
	}
}

void looreflect::LooReflectManager::regist_type(const looreflect::LooType *type,const char *moduleName) 
{
  m_Impl->regist_type(type, moduleName);
}

const looreflect::LooType *
looreflect::LooReflectManager::get_type(const char *nsname,const char *moduleName) 
{
  return m_Impl->get_type(looreflect::Hash(nsname), moduleName);
}

const looreflect::LooType *
looreflect::LooReflectManager::get_type(std::uint64_t hashvalue,const char *moduleName) 
{
  return m_Impl->get_type(hashvalue, moduleName);
}

void looreflect::LooReflectManager::remove_type (const char *nsname,
	const char *moduleName) {
	remove_type (looreflect::Hash (nsname), moduleName);
}

void looreflect::LooReflectManager::remove_type (std::uint64_t hashvalue, const char * moduleName)
{
	m_Impl->remove_type (hashvalue, moduleName);
}

#endif