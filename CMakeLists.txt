cmake_minimum_required(VERSION 3.0)

project(pfproject VERSION 0.1)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_executable(pfproject main.cpp usfml.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

target_link_libraries(
	pfproject
	sfml-graphics
	sfml-window
	sfml-system
)

#install(TARGETS usfml RUNTIME DESTINATION bin)
