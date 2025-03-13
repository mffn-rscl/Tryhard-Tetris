cmake_minimum_required(VERSION 3.10)
project(Tryhard Tetris)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(tetris-app main.cpp)
target_link_libraries(tetris-app sfml-graphics sfml-window sfml-system)
