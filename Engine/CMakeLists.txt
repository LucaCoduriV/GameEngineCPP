cmake_minimum_required(VERSION 3.20)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(header)


add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/assimp EXCLUDE_FROM_ALL)

file(GLOB files
        "header/vendor/*/*.h"
        "src/vendor/*/*.cpp"
        "header/vendor/*/*.hpp"
        )

add_library(Engine
        ${files}
        src/Shader.cpp
        header/Shader.hpp
        src/Renderer.cpp header/Renderer.hpp src/VertexBuffer.cpp header/VertexBuffer.hpp src/IndexBuffer.cpp header/IndexBuffer.hpp src/VertexArray.cpp header/VertexArray.hpp src/VertexBufferLayout.cpp header/VertexBufferLayout.hpp src/Texture.cpp header/Texture.hpp src/Camera.cpp header/Camera.hpp src/Window.cpp header/Window.hpp src/Events/Event.cpp header/Events/Event.hpp src/Events/ApplicationEvent.cpp header/Events/ApplicationEvent.hpp src/Events/EventDispatcher.cpp header/Events/EventDispatcher.hpp src/Events/MouseEvent.cpp header/Events/MouseEvent.hpp header/MouseCode.hpp src/App.cpp header/App.hpp src/Events/KeyEvent.cpp header/Events/KeyEvent.hpp header/KeyCode.hpp src/Layer.cpp header/Layer.hpp src/ModelLoader/ModelLoader.cpp header/ModelLoader/ModelLoader.hpp src/ModelLoader/Mesh.cpp header/ModelLoader/Mesh.hpp header/definitions.hpp)

target_precompile_headers(Engine PRIVATE header/pch.hpp)
target_include_directories(Engine PUBLIC header)
target_link_libraries(Engine
        glfw
        libglew_static
        glm
        assimp
        )