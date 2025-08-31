add_library(util STATIC
        parsing/tiny_obj_loader.h
        parsing/tiny_obj_loader.cpp
)

target_include_directories(util PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(util PUBLIC neon-deps)
