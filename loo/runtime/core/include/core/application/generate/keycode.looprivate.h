namespace looreflect
{

namespace detail
{

#ifndef __LOOREFLECT__
struct looggcoreggKeyCode_GlobalRegister{
looggcoreggKeyCode_GlobalRegister(){
looreflect::LooReflectManager::get().regist_type(looreflect::LooGetEnum<loo::core::KeyCode>(),REAL_MODULE_NAME);
}
~looggcoreggKeyCode_GlobalRegister(){
looreflect::LooReflectManager::get().remove_type(looreflect::Hash("loo::core::KeyCode"),REAL_MODULE_NAME);
}
};
looggcoreggKeyCode_GlobalRegister s_looggcoreggKeyCode_GlobalRegister;
#endif
} /* namespace detail */
} /* namespace looreflect */

