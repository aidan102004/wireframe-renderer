cmake_minimum_required(VERSION 3.16)
project(wireframe CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(wireframe
    src/main.cpp
    src/renderer.h
)
target_link_libraries(wireframe PRIVATE SDL2::SDL2)