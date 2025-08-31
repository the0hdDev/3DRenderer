add_executable(neon
        main.cpp
        shader/shader.cpp
        shader/shader.h
)

target_link_libraries(neon PRIVATE
        neon-deps
        util
)
