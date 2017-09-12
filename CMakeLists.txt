cmake_minimum_required(VERSION 3.8)
project(SoundGenX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

#--------------------------#
# Libraries
#--------------------------#
#Boost
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED)
list(APPEND SoundGenX_INCLUDE_DIRS "${BOOST_INCLUDE_DIRS}")
list(APPEND SoundGenX_LIBRARIES "${BOOST_LIBRARIES}")

# SFML
find_package(SFML REQUIRED network audio graphics window system)
list(APPEND SoundGenX_INCLUDE_DIRS ${SFML_INCLUDE_DIR})
list(APPEND SoundGenX_LIBRARIES ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

# OpenGL
find_package(OpenGL REQUIRED)

list(APPEND SoundGenX_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
list(APPEND SoundGenX_LIBRARIES ${OPENGL_LIBRARIES})

# SFGUI
add_subdirectory(SFGUI)
list(APPEND SoundGenX_INCLUDE_DIRS SFGUI/include)
list(APPEND SoundGenX_LIBRARIES sfgui)

# RTAudio
add_subdirectory(rtaudio)
list(APPEND SoundGenX_INCLUDE_DIRS rtaudio)
list(APPEND SoundGenX_INCLUDE_DIRS ${rtaudio_INCLUDE_DIR})
list(APPEND SoundGenX_LIBRARIES rtaudio)

#--------------------------#
# Executeable
#--------------------------#
file(GLOB_RECURSE SoundGenX_Sources source/*.cpp)
file(GLOB_RECURSE SoundGenX_Headers source/*.hpp)

add_executable(SoundGenX ${SoundGenX_Sources} ${SoundGenX_Headers})

target_include_directories(SoundGenX PRIVATE ${SoundGenX_INCLUDE_DIRS})
target_link_libraries(SoundGenX ${SoundGenX_LIBRARIES})
