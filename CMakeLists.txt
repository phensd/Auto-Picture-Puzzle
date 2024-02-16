cmake_minimum_required(VERSION 3.15)
project(PicturePuzzle)



add_executable(PicturePuzzle main.cpp puzzle.cpp puzzle_piece.cpp util.cpp)
target_include_directories(PicturePuzzle PRIVATE include)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")


if(WIN32)
	add_library(raylib STATIC IMPORTED)
	
	#This is where raylib installed on windows for me when generating a makefile with CMAKE and using MINGW-MAKE to make and install it.
	set_target_properties(PicturePuzzle raylib PROPERTIES
 	IMPORTED_LOCATION "C:/Program Files (x86)/raylib/lib/libraylib.a"
        INTERFACE_INCLUDE_DIRECTORIES "C:/Program Files (x86)/raylib/include")

	target_link_libraries(PicturePuzzle PRIVATE raylib winmm)

	#-mwindows gets rid of the console window that usually opens
	set(CMAKE_CXX_FLAGS_RELEASE "-O1 -s -mwindows")
ENDIF()

if(UNIX)
	#link with static raylib
	target_link_libraries(PicturePuzzle PRIVATE raylib.a)

	set(CMAKE_CXX_FLAGS_RELEASE "-O1 -s")
ENDIF()




set(CMAKE_CXX_FLAGS "-Wall -Wfatal-errors -Wextra -pedantic -Weffc++")





set_property(TARGET PicturePuzzle PROPERTY CXX_STANDARD 20)
