
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/core/object/object.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/core/object/object.cpp
)

source_group("core\\include\\core\\object" FILES ${LOCAL_PUBLIC})

source_group("core\\source\\core\\object" FILES ${LOCAL_PRIVATE})

# set(REFLECT_FILE_LIST
# object)
# DECL_GENFILES("looreflect\\include\\object")

set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)

set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

