#include "looreflect/looreflect.h"

#ifndef __LOOREFLECT__
#include "looreflect/looreflectmanager.h"
//register builtin types
//struct testggstdggstring_GlobalRegister {
//  testggstdggstring_GlobalRegister() {
//    looreflect::LooReflectManager::get().regist_type(
//        looreflect::LooGetClass<std::string>(), REAL_MODULE_NAME);
//  }
//};
//testggstdggstring_GlobalRegister s_testggstdggstring_GlobalRegister;

REGISTER_REFLECT_TYPE(std::string,std_string)

#define X(T, NAME, FMT)\
REGISTER_REFLECT_TYPE(T,NAME)
TYPES
#undef X


#endif