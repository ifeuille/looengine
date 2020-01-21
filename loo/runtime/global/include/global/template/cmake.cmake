
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/global/template/andornot.h
${MODULE_ROOT_PATH}/include/global/template/cacheresource.h
${MODULE_ROOT_PATH}/include/global/template/enumasbyte.h
${MODULE_ROOT_PATH}/include/global/template/external.h
${MODULE_ROOT_PATH}/include/global/template/externalstring.h
${MODULE_ROOT_PATH}/include/global/template/isvalidvariadicfunctionarg.h
${MODULE_ROOT_PATH}/include/global/template/refcounting.h
${MODULE_ROOT_PATH}/include/global/template/typehash.h
${MODULE_ROOT_PATH}/include/global/template/flags.h
${MODULE_ROOT_PATH}/include/global/template/hash.h
)



source_group("global\\include\\global\\template" FILES ${LOCAL_PUBLIC})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} 
${LOCAL_PUBLIC} 
)

