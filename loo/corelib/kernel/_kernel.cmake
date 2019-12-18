set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/kernel/loometaobject_reflect_p.h
${MODULE_ROOT_PATH}/kernel/loometatype.h
${MODULE_ROOT_PATH}/kernel/loovariant.h
${MODULE_ROOT_PATH}/kernel/loometaobject.h
${MODULE_ROOT_PATH}/kernel/looobjectdefs.h
${MODULE_ROOT_PATH}/kernel/looobjectdefs_impl.h
)

set(LOCAL_PRIVATE 
${MODULE_ROOT_PATH}/kernel/loometatype.cpp
${MODULE_ROOT_PATH}/kernel/loometaobject.cpp
)


source_group("corelib\\kernel\\header" FILES ${LOCAL_PUBLIC})
source_group("corelib\\kernel\\source" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})