cmake_minimum_required(VERSION 3.20)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(header)


add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

file(GLOB files
        "header/vendor/*/*.h"
        "src/vendor/*/*.cpp"
        "header/vendor/*/*.hpp"
        )

add_executable(App
        ${files}
        src/Application.cpp
        src/Shader.cpp
        header/Shader.hpp
        src/Renderer.cpp header/Renderer.hpp src/VertexBuffer.cpp header/VertexBuffer.hpp src/IndexBuffer.cpp header/IndexBuffer.hpp src/VertexArray.cpp header/VertexArray.hpp src/VertexBufferLayout.cpp header/VertexBufferLayout.hpp src/Texture.cpp header/Texture.hpp src/Camera.cpp header/Camera.hpp)


target_link_libraries(App
        glfw
        libglew_static
        glm
        )