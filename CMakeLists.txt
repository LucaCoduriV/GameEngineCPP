cmake_minimum_required(VERSION 3.20)
project(GameEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(GameEngine/Header)
add_subdirectory(GameEngine/Source)


add_definitions(-DGLEW_STATIC)
add_subdirectory(Lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(Lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(Lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(GameEngine
        glfw
        libglew_static
        glm
        )

#target_include_directories(GameEngine
#        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
#        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
#        )