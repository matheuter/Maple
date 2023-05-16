set(MODULE_NAME qsynedit)

option(BUILD_BY_SHARED "指定 robbin 将构建为动态库" ON)

if(TRUE)
    spark_file_glob(Header
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/exporter/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/highlighter/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/formatter/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/searcher/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/syntaxer/*.cpp
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/qt_utils/*.cpp
    )
    spark_file_glob(Source
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/highlighter/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/exporter/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/searcher/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/formatter/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/syntaxer/*.h
        ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit/qt_utils/*.cpp
    )
    if(BUILD_BY_SHARED)
        spark_add_library(${MODULE_NAME} SHARED ${Source} ${Header})
    else()
        spark_add_library(${MODULE_NAME} STATIC ${Source} ${Header})
    endif(BUILD_BY_SHARED)

    target_include_directories(${MODULE_NAME} PRIVATE ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit)
    target_include_directories(${MODULE_NAME} PUBLIC  ${KNOWLEDGE_PROJECT_PATH}/depends/qsynedit)

    if(USE_QT6)
        target_link_qt6(${MODULE_NAME})
    else()
        target_link_qt5(${MODULE_NAME})
        target_link_qt5_Xml(${MODULE_NAME})
    endif(USE_QT6)

endif(TRUE)

if(WIN32)
    # 在 Windows 中构建时，需要关注此库的构建形式
    target_compile_definitions(${MODULE_NAME}
        PRIVATE 
    )
endif(WIN32)

if(UNIX)
    # 在 Linux 中构建时，需要关注此库的构建形式，QScintilla 应该以何种方式编译
    target_compile_definitions(${MODULE_NAME}
        PRIVATE 
           # SA_RIBBON_BAR_NO_EXPORT
    )
endif(UNIX)
