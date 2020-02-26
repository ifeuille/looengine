
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/event/event.h
)





set(LOCAL_PRIVATE

)
#${MODULE_ROOT_PATH}/source/global/container/customizedstreambuf.cpp

source_group("global\\include\\global\\event" FILES ${LOCAL_PUBLIC})
source_group("global\\source\\global\\event" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC}
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE} 
${LOCAL_PRIVATE}
)