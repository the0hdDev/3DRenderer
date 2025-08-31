cmake_minimum_required(VERSION 3.31)
project(neon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Abhängigkeiten nur einmal suchen
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

# Dummy-Target, das nur die Libs weiterreicht
add_library(neon-deps INTERFACE
        util/parsing/parser.cpp)
target_link_libraries(neon-deps INTERFACE
        OpenGL::GL
        glfw
        glad::glad
)

# Jetzt deine Projekte
add_subdirectory(core)
add_subdirectory(util)