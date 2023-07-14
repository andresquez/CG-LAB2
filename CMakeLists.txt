cmake_minimum_required(VERSION 3.26)

project(FB VERSION 1.0)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/framebuffer.h
)
