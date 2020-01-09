
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/object/object.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/object/object.cpp
)


source_group("looreflect\\include\\object" FILES ${LOCAL_PUBLIC})

source_group("looreflect\\source\\object" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

