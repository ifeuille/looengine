
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/stream/stream.h
${MODULE_ROOT_PATH}/include/global/stream/memstream.h
${MODULE_ROOT_PATH}/include/global/stream/filestream.h
)


set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/stream/stream.cpp
${MODULE_ROOT_PATH}/source/global/stream/filestream.cpp
)



source_group("global\\include\\global\\stream" FILES ${LOCAL_PUBLIC})
source_group("global\\source\\global\\stream" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)


set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

