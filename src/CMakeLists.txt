include(../cmake/build/buildruntime.cmake)

set(QRC_SOURCES ../resource/images.qrc)

knowledge_global_include(
        runtime
        rustparser
)

spark_file_glob(SOURCES
    interface/*.h
    core/actor/*.h
    core/actor/*.cpp
    core/pluginsystem/*.cpp
    core/pluginsystem/*.h
    widgets/dockwidget/*.h
    widgets/dockwidget/*.cpp
    rustparser/*.h
    rustparser/*.cpp
    *.h
    *.cpp
    *.ui
)

spark_add_executable(${PROJECT_NAME} ${QRC_SOURCES} ${SOURCES})

target_link_qt5(${PROJECT_NAME})
target_link_qt5_Network(${PROJECT_NAME})
target_link_qt5_Printsupport(${PROJECT_NAME})
target_link_qt5_Xml(${PROJECT_NAME})
target_link_qt5_Concurrent(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} user32 runtime)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
    )
endif(WIN32)

if(UNIX)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
           SA_RIBBON_BAR_NO_EXPORT
    )
endif(UNIX)
