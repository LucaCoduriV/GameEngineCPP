cmake_minimum_required(VERSION 3.20)
project(Entt)

set(CMAKE_CXX_STANDARD 17)


add_library(Entt INTERFACE entt.hpp)
target_include_directories(Entt INTERFACE .)