cmake_minimum_required(VERSION 3.8)
project(SoundGenX)

set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE SoundGenX_Sources source/*.cpp)
file(GLOB_RECURSE SoundGenX_Headers source/*.hpp)

add_executable(SoundGenX ${SoundGenX_Sources} ${SoundGenX_Headers})
