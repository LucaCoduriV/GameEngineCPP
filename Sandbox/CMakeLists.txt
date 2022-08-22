cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

add_executable(Sandbox main.cpp TestLayer.cpp TestLayer.hpp LightLayer.cpp
        LightLayer.hpp modelLoader/ModelLoaderLayer.cpp modelLoader/ModelLoaderLayer.hpp)
target_link_libraries(Sandbox PRIVATE Engine)


#FILE(COPY res/ DESTINATION "${CMAKE_BINARY_DIR}/${NAME}/res")