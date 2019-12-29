set(LLVM_LINK_COMPONENTS Support)
add_clang_executable(looreflect
	annotations.h
	enumconstantgenerator.h
	fieldgenerator.h
	functiongenerator.h
	loofinder.h
	looreflectedclass.h
	looreflectedclass.cpp
	looreflectedenum.h
	looreflectedenum.cpp
	utils.h
	utils.cpp
    main.cpp
)

target_link_libraries(looreflect
    PRIVATE
    clangTooling
    clangBasic
    clangASTMatchers
)

