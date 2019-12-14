PROJECT(looreflect)
 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(TARGET looreflect)

SET(HDRS 
    cbordevice.h
    commandlineoption.h
    commandlineparser.h 
    debug.h 
    dir.h 
    fileinfo.h 
    generator.h 
    looreflect.h 
    outputrevision.h 
    parser.h 
    preprocessor.h 
    token.h 
    utils.h 
    diriterator.h
    symbols.h
    )
SET(SRCS 
    commandlineoption.cpp
    commandlineparser.cpp
    dir.cpp
    fileinfo.cpp
    generator.cpp
    keywords.cpp
    looreflect.cpp
    main.cpp
    parser.cpp
    ppkeywords.cpp
    preprocessor.cpp
    token.cpp
    diriterator.cpp
    )

# set(output_path "${CMAKE_CURRENT_SOURCE_DIR}")
# MESSAGE("CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
# add_custom_command(
#         OUTPUT ${output_path}
#         COMMAND generate_keywords${LOO_COMPILER_VERSION}
#                 -o ${output_path} "keywords.cpp"
#         DEPENDS generate_keywords
#         COMMENT "Compiling material keywords.cpp to ${output_path}"
# )
# add_custom_command(
#     OUTPUT ${output_path}
#     COMMAND generate_keywords ${MATC_FLAGS} -p "preprocessor"
#             -o ${output_path} "keywords.cpp"
#     DEPENDS generate_keywords
#     COMMENT "Compiling material keywords.cpp to ${output_path}"
# )

add_program(${TARGET})
declare_program(${TARGET})
#add_executable(${TARGET} ${HDRS} ${SRCS})
set_property(TARGET ${TARGET} PROPERTY FOLDER "loo/tools")

