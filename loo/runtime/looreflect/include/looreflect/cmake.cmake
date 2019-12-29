
set(LOCAL_PUBLIC
    ${MODULE_ROOT_PATH}/include/looreflect/looreflect.h
    ${MODULE_ROOT_PATH}/include/looreflect/decltype.h
    ${MODULE_ROOT_PATH}/include/looreflect/declenum.h
    ${MODULE_ROOT_PATH}/include/looreflect/declclass.h
    ${MODULE_ROOT_PATH}/include/looreflect/builtintypevector.h
    ${MODULE_ROOT_PATH}/include/looreflect/builtintypeunorderedmap.h
    ${MODULE_ROOT_PATH}/include/looreflect/builtintypestring.h
    ${MODULE_ROOT_PATH}/include/looreflect/builtinpodtypes.h
    ${MODULE_ROOT_PATH}/include/looreflect/looreflectmanager.h
    ${MODULE_ROOT_PATH}/include/looreflect/dllexport.h
)

set(LOCAL_PRIVATE
    ${MODULE_ROOT_PATH}/source/looreflect/looreflect.cpp
    ${MODULE_ROOT_PATH}/source/looreflect/looreflectmanager.cpp
)

source_group("looreflect\\include\\looreflect" FILES ${LOCAL_PUBLIC})
source_group("looreflect\\source\\looreflect" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})