
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/object/object.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/object/object.cpp
${MODULE_ROOT_PATH}/source/object/privatemodule.h
)

source_group("looreflect\\include\\object" FILES ${LOCAL_PUBLIC})

source_group("looreflect\\source\\object" FILES ${LOCAL_PRIVATE})

# set(REFLECT_FILE_LIST
# object)
# DECL_GENFILES("looreflect\\include\\object")

set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)

set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

