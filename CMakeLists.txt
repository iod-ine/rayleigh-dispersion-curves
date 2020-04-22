cmake_minimum_required(VERSION 3.16)
project(RDCs)

set(CMAKE_CXX_STANDARD 20)

include_directories(src libs/include)

add_executable(RDCs main.cpp src/medium.cpp src/medium.h src/layer.cpp src/layer.h)