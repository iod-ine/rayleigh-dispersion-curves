cmake_minimum_required(VERSION 3.16)
project(rdcscalc)

set(CMAKE_CXX_STANDARD 20)

include_directories(src libs/include)

add_executable(rdcscalc main.cpp src/medium.cpp src/medium.h src/layer.cpp src/layer.h src/rayleigh.h src/rayleigh_layer_matrix.cpp src/rayleigh_dispersion_function.cpp src/rdc_utils.cpp src/rdc_utils.h src/rayleigh_funamental_mode.cpp src/rayleigh_next_higher_mode.cpp src/load_model_from_file.cpp)