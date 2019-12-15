PROJECT(looreflect)
 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
set(TARGET looreflect)

SET(HDRS 
    cbordevice.h
    commandlineoption.h
    commandlineparser.h 
    debug.h 
    generator.h 
    looreflect.h 
    outputrevision.h 
    parser.h 
    preprocessor.h 
    token.h 
    utils.h 
    symbols.h
    stringlist.h
    )
SET(SRCS 
    commandlineoption.cpp
    commandlineparser.cpp
    generator.cpp
    keywords.cpp
    looreflect.cpp
    main.cpp
    parser.cpp
    ppkeywords.cpp
    preprocessor.cpp
    token.cpp
    )
SET(FILESYSTEM_HDRS
    ghc/filesystem.hpp
    ghc/fs_fwd.hpp
    ghc/fs_impl.hpp
    ghc/fs_std_fwd.hpp
    ghc/fs_std_impl.hpp
    ghc/fs_std.hpp
    ghc/fs_utils.hpp)
SET(nlohmann_HDRS
nlohmann/json.hpp)

source_group("filesystem" FILES ${FILESYSTEM_HDRS})
source_group("nlohmann" FILES ${nlohmann_HDRS})
SET(HDRS ${HDRS} ${FILESYSTEM_HDRS} ${nlohmann_HDRS})
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

