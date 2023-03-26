cmake_minimum_required(VERSION 3.24)
project(narccissus)

set(CMAKE_CXX_STANDARD 23)

# Include GLFW
#add_subdirectory(external/glfw-3.3.8)
#include_directories(external/glfw-3.3.8/include)

#include GLM
#add_subdirectory(external/glm)

# Include Glad
#add_library(glad STATIC external/glad/src/glad.c)
#include_directories(external/glad/include)


add_executable(narccissus include/Vec3.hpp include/Util.hpp include/Wave.hpp include/Face.hpp include/Mesh.hpp include/Path.hpp include/Nrcc.hpp tests/emWave.cpp)

# Link GLFW and Glad libraries
#target_link_libraries(narccissus glfw glad glm)

