add_library(util STATIC
        parsing/objLoaderBackend.h
        parsing/objLoader.h
        parsing/objLoader.cpp
)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(util PUBLIC neon-deps)
