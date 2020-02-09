
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/algorithms/stringutils.h
${MODULE_ROOT_PATH}/include/global/algorithms/stringparser.h
)


set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/algorithms/stringparser.cpp
)



source_group("global\\include\\global\\algorithms" FILES ${LOCAL_PUBLIC})
source_group("global\\source\\global\\algorithms" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)


set(SOURCE_PRIVATE ${SOURCE_PRIVATE} 
${LOCAL_PRIVATE} 
)

