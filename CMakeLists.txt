cmake_minimum_required(VERSION 3.5.1)

project(Maple LANGUAGES C CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)

include(cmake/SparkEnvConfig.cmake)
include(cmake/SparkMacrosConfig.cmake)

include(cmake/SparkFindLibraries.cmake)
include(cmake/SparkFindQt5Config.cmake)

include(cmake/SparkMacrosExtendConfig.cmake)
include(cmake/SparkInstallMacrosConfig.cmake)

include(cmake/KIncludeConfig.cmake)
include(cmake/KMacroMessage.cmake)
include(cmake/KModuleConfig.cmake)

option(BUILD_PLUGINS        "build plugin"                      ON)
option(BUILD_WITH_TEST      "build with test"                   ON)

add_compile_options(/wd4251)
add_compile_options(/wd4275)

set(KNOWLEDGE_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

knowledge_global_include(
        src/core/actor/
        src/interface/
        src/widgets/dockwidget
        src/core/pluginsystem
        src/widgets
)

add_subdirectory(depends)
add_subdirectory(src)
