# tools-extension-config.cmake

# 内容：
    # 对 buildin.cmake 中的内容进行抽象

# 早期，每个模块中都以该结构为描述，现在，只保留一个 SOURCE_PATHS
if(false)
    set(SOURCE_FILES "")

    set(SOURCE_PATHS
        ${CMAKE_CURRENT_LIST_DIR}
    )

    foreach(PATH IN LISTS SOURCE_PATHS)
        spark_file_glob(SOURCES 
            ${PATH}/*.h 
            ${PATH}/*.cpp 
            ${PATH}/*.ui 
            ${PATH}/*.qrc)
        list(APPEND SOURCE_FILES ${SOURCES})
    endforeach(PATH IN LISTS SOURCE_PATHS)

    list(APPEND TOOLS_MODULES_SOURCES ${SOURCE_FILES})
endif(false)

# 每个模块中都以该结构为描述，现在，只保留一个 SOURCE_PATHS
macro(add_tools_module_source_paths)
    set(SOURCE_FILES "")

    set(SOURCE_PATHS
        ${ARGN}
    )

    foreach(PATH IN LISTS SOURCE_PATHS)
        spark_file_glob(SOURCES 
            ${PATH}/*.h 
            ${PATH}/*.cpp 
            ${PATH}/*.ui 
            ${PATH}/*.qrc)
        list(APPEND SOURCE_FILES ${SOURCES})
    endforeach(PATH IN LISTS SOURCE_PATHS)

    list(APPEND TOOLS_MODULES_SOURCES ${SOURCE_FILES})
endmacro(add_tools_module_source_paths)


# 1. 在模块中使用
# find_package(tools-extension PATHS cmake/modules)

# add_tools_module_source_paths(
#     ${CMAKE_CURRENT_LIST_DIR}
#     ${CMAKE_CURRENT_LIST_DIR}/MoreSourceDir
# )