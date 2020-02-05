cmake_minimum_required (VERSION 3.8)

project ("mazer" 
	VERSION 1.1 
	DESCRIPTION "A QT supported Maze Game in OpenGL 4.4" 
	LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# build the following
add_subdirectory ("src")