
# set(LOCAL_PUBLIC     
# ${MODULE_ROOT_PATH}/include/core/context.h
# ${MODULE_ROOT_PATH}/include/core/dllexporter.h
# )

# set(LOCAL_PRIVATE
   # ${MODULE_ROOT_PATH}/source/core/context.cpp
   # ${MODULE_ROOT_PATH}/source/core/declreflect.h
# )

file( GLOB_RECURSE LOCAL_PUBLIC "*.h" )
file( GLOB_RECURSE LOCAL_PRIVATE "*.cpp" )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LOCAL_PUBLIC} )
source_group( TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${LOCAL_PRIVATE} )


#source_group("core\\include\\core" FILES ${LOCAL_PUBLIC})
#source_group("core\\source\\core" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})