cmake_minimum_required(VERSION 3.31)
project(3D)

set(CMAKE_CXX_STANDARD 20)

add_executable(My3D   src/main.cpp
                    src/openglErrorReporting.cpp
                    src/shdr.h
                    src/shdr.cpp

)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Linken
target_link_libraries(My3D PRIVATE
        OpenGL::GL
        glfw
        glad::glad
)