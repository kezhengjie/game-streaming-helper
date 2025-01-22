cmake_minimum_required(VERSION 3.13)

project(game-streaming-helper)

set(CMAKE_CXX_STANDARD 17)

include_directories(third_party/json/include)

add_executable(game-streaming-helper main.cpp util.cpp)
add_executable(test test.cpp util.cpp)
