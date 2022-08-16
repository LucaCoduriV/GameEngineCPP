cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

SET(NAME Sandbox)

add_executable(${NAME} main.cpp TestLayer.cpp TestLayer.hpp LightLayer.cpp LightLayer.hpp)
add_executable(EcsTest EcsTest/main.cpp)
target_link_libraries(${NAME} PRIVATE Engine Ecs)
target_link_libraries(EcsTest PRIVATE Engine Ecs)

FILE(COPY res/ DESTINATION "${CMAKE_BINARY_DIR}/${NAME}/res")