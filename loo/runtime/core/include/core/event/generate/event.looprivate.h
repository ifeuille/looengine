namespace looreflect
{

namespace detail
{

#ifndef __LOOREFLECT__
struct looggcoreggEvent_GlobalRegister{
looggcoreggEvent_GlobalRegister(){
looreflect::LooReflectManager::get().regist_type(looreflect::LooGetClass<loo::core::Event>(),REAL_MODULE_NAME);
}
~looggcoreggEvent_GlobalRegister(){
looreflect::LooReflectManager::get().remove_type(looreflect::Hash("loo::core::Event"),REAL_MODULE_NAME);
}
};
looggcoreggEvent_GlobalRegister s_looggcoreggEvent_GlobalRegister;
#endif
} /* namespace detail */
} /* namespace looreflect */

namespace looreflect
{

namespace detail
{

#ifndef __LOOREFLECT__
struct looggcoreggEventListener_GlobalRegister{
looggcoreggEventListener_GlobalRegister(){
looreflect::LooReflectManager::get().regist_type(looreflect::LooGetClass<loo::core::EventListener>(),REAL_MODULE_NAME);
}
~looggcoreggEventListener_GlobalRegister(){
looreflect::LooReflectManager::get().remove_type(looreflect::Hash("loo::core::EventListener"),REAL_MODULE_NAME);
}
};
looggcoreggEventListener_GlobalRegister s_looggcoreggEventListener_GlobalRegister;
#endif
} /* namespace detail */
} /* namespace looreflect */

namespace looreflect
{

namespace detail
{

#ifndef __LOOREFLECT__
struct looggcoreggEventManager_GlobalRegister{
looggcoreggEventManager_GlobalRegister(){
looreflect::LooReflectManager::get().regist_type(looreflect::LooGetClass<loo::core::EventManager>(),REAL_MODULE_NAME);
}
~looggcoreggEventManager_GlobalRegister(){
looreflect::LooReflectManager::get().remove_type(looreflect::Hash("loo::core::EventManager"),REAL_MODULE_NAME);
}
};
looggcoreggEventManager_GlobalRegister s_looggcoreggEventManager_GlobalRegister;
#endif
} /* namespace detail */
} /* namespace looreflect */

