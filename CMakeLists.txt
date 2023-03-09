cmake_minimum_required(VERSION 3.24)
project(narccissus)

set(CMAKE_CXX_STANDARD 23)

add_executable(narccissus include/Vector.hpp include/Nrcc.hpp include/Ray.hpp include/Face.hpp include/Path.hpp main.cpp)
