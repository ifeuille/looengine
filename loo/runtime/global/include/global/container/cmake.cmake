
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/container/arrayref.h
${MODULE_ROOT_PATH}/include/global/container/comptr.h
${MODULE_ROOT_PATH}/include/global/container/customizedstreambuf.h
${MODULE_ROOT_PATH}/include/global/container/appendable.h
${MODULE_ROOT_PATH}/include/global/container/bittree.h
${MODULE_ROOT_PATH}/include/global/container/iterators.h
${MODULE_ROOT_PATH}/include/global/container/inplace.h
${MODULE_ROOT_PATH}/include/global/container/untypedstorage.h
${MODULE_ROOT_PATH}/include/global/container/fixedtuplearray.h
${MODULE_ROOT_PATH}/include/global/container/chunkedindexedpool.h
${MODULE_ROOT_PATH}/include/global/container/cachedindexedpool.h


)





set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/global/container/customizedstreambuf.cpp
)


source_group("global\\include\\global\\container" FILES ${LOCAL_PUBLIC})
source_group("global\\source\\global\\container" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC}
)


set(SOURCE_PRIVATE 
${SOURCE_PRIVATE} 
${LOCAL_PRIVATE}
)