set(MODULE_NAME runtime)
set(CMAKE_BUILD_TYPE "Release")

option(BUILD_BY_SHARED "指定 runtime 将构建为动态库" OFF)

if(TRUE)
    spark_file_glob(Header
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/support/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/atn/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/dfa/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/internal/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/misc/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/pattern/*.h
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/xpath/*.h
    )

    spark_file_glob(Source
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/support/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/atn/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/dfa/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/internal/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/misc/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/pattern/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/src/runtime/tree/xpath/*.cpp
    )

    if(BUILD_BY_SHARED)
        spark_add_library(${MODULE_NAME} SHARED ${Source} ${Header})
    else()
        spark_add_library(${MODULE_NAME} STATIC ${Source} ${Header})
    endif(BUILD_BY_SHARED)

    target_include_directories(${MODULE_NAME} PRIVATE ${KNOWLEDGE_PROJECT_PATH}/src/runtime)
    target_include_directories(${MODULE_NAME} PUBLIC  ${KNOWLEDGE_PROJECT_PATH}/src/runtime)
    find_package(Threads REQUIRED)
    target_link_libraries(${MODULE_NAME} Threads::Threads)
endif(TRUE)

if(WIN32)
    # 在 Windows 中构建时，需要关注此库的构建形式
    target_compile_definitions(${MODULE_NAME}
        PRIVATE 
           ANTLR4CPP_EXPORTS
    )
endif(WIN32)

if(UNIX)
    # 在 Linux 中构建时，需要关注此库的构建形式，QScintilla 应该以何种方式编译
    target_compile_definitions(${MODULE_NAME}
        PRIVATE 
           # SA_RIBBON_BAR_NO_EXPORT
    )
endif(UNIX)

spark_add_link(${MODULE_NAME})
