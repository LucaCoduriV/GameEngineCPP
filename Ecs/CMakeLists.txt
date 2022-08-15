cmake_minimum_required(VERSION 3.20)
project(Ecs)

set(CMAKE_CXX_STANDARD 17)


add_library(Ecs INTERFACE Ecs.hpp)
target_include_directories(Ecs INTERFACE .)