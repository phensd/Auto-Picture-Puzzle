cmake_minimum_required(VERSION 3.15)
project(PicturePuzzle)

find_package(raylib 3.0 REQUIRED)

add_executable(PicturePuzzle main.cpp puzzle.cpp puzzle_piece.cpp)



target_include_directories(PicturePuzzle PRIVATE include)

target_link_libraries(PicturePuzzle PRIVATE raylib)



set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -s")


set_property(TARGET PicturePuzzle PROPERTY CMAKE_CXX_STANDARD 20)
