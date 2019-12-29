
set(LOCAL_PUBLIC
${MODULE_ROOT_PATH}/include/plog/Init.h
${MODULE_ROOT_PATH}/include/plog/Log.h
${MODULE_ROOT_PATH}/include/plog/Logger.h
${MODULE_ROOT_PATH}/include/plog/Record.h
${MODULE_ROOT_PATH}/include/plog/Severity.h
${MODULE_ROOT_PATH}/include/plog/Util.h
${MODULE_ROOT_PATH}/include/plog/WinApi.h
${MODULE_ROOT_PATH}/include/plog/Record.h
${MODULE_ROOT_PATH}/include/plog/Record.h
)
set(LOCAL_APPENDERS_PUBLIC
${MODULE_ROOT_PATH}/include/plog/Appenders/AndroidAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/ColorConsoleAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/ConsoleAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/DebugOutputAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/EventLogAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/IAppender.h
${MODULE_ROOT_PATH}/include/plog/Appenders/RollingFileAppender.h
)
set(LOCAL_CONVERTERS_PUBLIC
${MODULE_ROOT_PATH}/include/plog/Converters/NativeEOLConverter.h
${MODULE_ROOT_PATH}/include/plog/Converters/UTF8Converter.h
)
set(LOCAL_FORMATTERS_PUBLIC
${MODULE_ROOT_PATH}/include/plog/Formatters/CsvFormatter.h
${MODULE_ROOT_PATH}/include/plog/Formatters/FuncMessageFormatter.h
${MODULE_ROOT_PATH}/include/plog/Formatters/MessageOnlyFormatter.h
${MODULE_ROOT_PATH}/include/plog/Formatters/TxtFormatter.h
)
set(LOCAL_PRIVATE
${MODULE_ROOT_PATH}/source/plog/empty.cpp
)

source_group("plog\\include\\plog" FILES ${LOCAL_PUBLIC})
source_group("plog\\include\\plog\\Appenders" FILES ${LOCAL_APPENDERS_PUBLIC})
source_group("plog\\include\\plog\\Converters" FILES ${LOCAL_CONVERTERS_PUBLIC})
source_group("plog\\include\\plog\\Formatters" FILES ${LOCAL_FORMATTERS_PUBLIC})


set(SOURCE_PUBLIC ${SOURCE_PUBLIC} ${LOCAL_PUBLIC} ${LOCAL_APPENDERS_PUBLIC} ${LOCAL_CONVERTERS_PUBLIC} ${LOCAL_FORMATTERS_PUBLIC}) 
set(SOURCE_PRIVATE ${SOURCE_PRIVATE} ${LOCAL_PRIVATE})