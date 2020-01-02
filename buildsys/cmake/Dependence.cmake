
MACRO(dep_module_include _module_name)
    INCLUDE_DIRECTORIES(${LOO_RUNTIME_ROOT_DIR}/${_module_name}/include)
ENDMACRO(dep_module_include)


MACRO(dep_tinyutils)
    INCLUDE_DIRECTORIES(${LOO_THIRDPART_ROOT_DIR}/tinyutils)
ENDMACRO(dep_tinyutils)


MACRO(add_dep_7z)
    #set(EXTRA_LINKED_LIBRARIES ${EXTRA_LINKED_LIBRARIES} ${...})
    ADD_DEFINITIONS(-DGLM_FORCE_RADIANS)
    include_directories(${LOO_THIRDPART_ROOT_DIR}/7z)
    #link_directories(${LEngine_DEPDENCY_ROOT_DIR}/7z/lib/win_x64)
ENDMACRO(add_dep_7z)

MACRO(add_dep_glm)
    include_directories(${LOO_THIRDPART_ROOT_DIR}/glm)
ENDMACRO(add_dep_glm)