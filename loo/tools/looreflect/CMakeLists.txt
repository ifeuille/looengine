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
    )

add_program(${TARGET})
declare_program(${TARGET})
#add_executable(${TARGET} ${HDRS} ${SRCS})
set_property(TARGET ${TARGET} PROPERTY FOLDER "loo/tools")

