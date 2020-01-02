
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/filemanager/dllexporter.h
${MODULE_ROOT_PATH}/include/filemanager/LZMACodec.h
${MODULE_ROOT_PATH}/include/filemanager/package.h
${MODULE_ROOT_PATH}/include/filemanager/residentifier.h
${MODULE_ROOT_PATH}/include/filemanager/resloader.h
)

set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/filemanager/ArchiveExtractCallback.cpp
${MODULE_ROOT_PATH}/source/filemanager/ArchiveExtractCallback.h
${MODULE_ROOT_PATH}/source/filemanager/ArchiveOpenCallback.cpp
${MODULE_ROOT_PATH}/source/filemanager/ArchiveOpenCallback.h
${MODULE_ROOT_PATH}/source/filemanager/LZMACodec.cpp
${MODULE_ROOT_PATH}/source/filemanager/package.cpp
${MODULE_ROOT_PATH}/source/filemanager/resloader.cpp
${MODULE_ROOT_PATH}/source/filemanager/streams.cpp
${MODULE_ROOT_PATH}/source/filemanager/streams.h
)

source_group("filemanager\\include\\filemanager" FILES ${LOCAL_PUBLIC})
source_group("filemanager\\source\\filemanager" FILES ${LOCAL_PRIVATE})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC})
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})