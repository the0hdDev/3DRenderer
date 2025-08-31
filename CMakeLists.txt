cmake_minimum_required(VERSION 3.31)
project(neon LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_library(neon-deps INTERFACE)
target_link_libraries(neon-deps INTERFACE
        OpenGL::GL
        glfw
        glad::glad
)

add_subdirectory(util)
add_subdirectory(core)
