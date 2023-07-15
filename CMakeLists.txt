cmake_minimum_required(VERSION 3.12)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)

add_executable(GameOfLife src/main.cpp)

target_include_directories(GameOfLife PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(GameOfLife ${SDL2_LIBRARIES})
