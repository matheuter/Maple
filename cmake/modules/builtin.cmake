# builtin.cmake

# find_tools_modules
macro(find_tools_modules MODULE_VAR)
    spark_file_glob(${MODULE_VAR} ${ARGN})
endmacro(find_tools_modules MODULE_VAR)

# load_modules 预定义模块加载宏
macro(load_tools_modules MODULE_VAR)
    foreach(module IN LISTS ${MODULE_VAR})
        include(${module})
    endforeach(module IN LISTS ${MODULE_VAR})
endmacro(load_tools_modules MODULE_VAR)


# 查找所有 tools.cmake 与 tools-dependency.cmake 模块
    # tools.cmake 即刻加载
    # tools-dependency.cmake 后续加载
find_tools_modules(TOOLS_MODULES 
    extensions/builtin/*/tools.cmake)
find_tools_modules(TOOLS_DEPENDENCY_MODULES 
    extensions/builtin/*/tools-dependency.cmake)
