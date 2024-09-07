cmake_minimum_required(VERSION 3.20.0)
project(lab-camera VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_library(MATH_LIBRARY m)

link_libraries( ${MATH_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )


add_compile_options(-std=c++20 -Wall -Wextra -Wconversion -Wpedantic)

add_executable(program1 program1.cpp)
add_executable(program2 program2.cpp)
add_executable(program3 program3.cpp)
