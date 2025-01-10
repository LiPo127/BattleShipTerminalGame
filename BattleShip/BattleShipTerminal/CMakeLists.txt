# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add the executable that will be built
add_executable(BattleShip main.cpp)

# You can also include directories if needed (for example, if func.h is in a subfolder)
include_directories(${CMAKE_SOURCE_DIR})
