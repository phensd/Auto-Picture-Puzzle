cmake_minimum_required(VERSION 3.15)
project(PicturePuzzle)


add_executable(PicturePuzzle main.cpp puzzle.cpp puzzle_piece.cpp util.cpp)

target_include_directories(PicturePuzzle PRIVATE include)

#link with static raylib
target_link_libraries(PicturePuzzle PRIVATE raylib.a)



set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Weffc++")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O1 -s")


set_property(TARGET PicturePuzzle PROPERTY CXX_STANDARD 20)
