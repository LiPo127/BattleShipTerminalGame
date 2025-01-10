cmake_minimum_required(VERSION 3.10)

project(Battleship)

set(CMAKE_C_STANDARD 11)

add_executable(BattleShip main.c)

include_directories(${CMAKE_SOURCE_DIR})
