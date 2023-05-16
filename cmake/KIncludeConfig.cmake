
macro(knowledge_global_include __global_incude_dirs)
        set(__include_dir_items ${ARGN})
        foreach(__include_dir_item IN LISTS __include_dir_items)
                include_directories(${KNOWLEDGE_PROJECT_PATH}/${__include_dir_item})
        endforeach()
endmacro()

macro(knowledge_private_include __private_incude_dirs)
        set(__include_dir_items ${ARGN})
        foreach(__include_dir_item IN LISTS __include_dir_items)
                include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${__include_dir_item})
        endforeach()
endmacro()

if(WIN32)
    add_compile_definitions(_UNICODE= UNICODE=)
endif()

if (MSVC)
        add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
        add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif (MSVC)
