cmake_minimum_required(VERSION 3.2)
project(narccissus)

set(CMAKE_CXX_STANDARD 23)

# Include GLFW
#add_subdirectory(external/glfw-3.3.8)
#include_directories(external/glfw-3.3.8/include)

#include GLM
#add_subdirectory(external/glm)

# Include Glad
#add_library(glad STATIC external/glad/src/glad.c tests/test_graph.cpp)
#include_directories(external/glad/include)


add_executable(narccissus src/Vec3.hpp src/Util.hpp src/Wave.hpp src/Face.hpp src/Mesh.hpp tests/test_donut.cpp src/Pole.hpp)

# Link GLFW and Glad libraries
#target_link_libraries(narccissus glfw glad glm)

