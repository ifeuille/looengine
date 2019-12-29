
MACRO(dep_module_include _module_name)
    INCLUDE_DIRECTORIES(${LOO_RUNTIME_ROOT_DIR}/${_module_name}/include)
ENDMACRO(dep_module_include)