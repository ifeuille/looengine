set(LOCAL_PUBLIC     
${MODULE_ROOT_PATH}/kernel/loometaobject_reflect_p.h
)


source_group("corelib\\kernel\\header" FILES ${LOCAL_PUBLIC})
#source_group("Core\\Private" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
##set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})