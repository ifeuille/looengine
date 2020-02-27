namespace looreflect
{

namespace detail
{

#ifndef __LOOREFLECT__
struct looggObject_GlobalRegister{
looggObject_GlobalRegister(){
looreflect::LooReflectManager::get().regist_type(looreflect::LooGetClass<loo::Object>(),REAL_MODULE_NAME);
}
~looggObject_GlobalRegister(){
looreflect::LooReflectManager::get().remove_type(looreflect::Hash("loo::Object"),REAL_MODULE_NAME);
}
};
looggObject_GlobalRegister s_looggObject_GlobalRegister;
#endif
} /* namespace detail */
} /* namespace looreflect */

