cmake_minimum_required(VERSION 3.20.0)
project(lab-1 VERSION 1.0.0 LANGUAGES C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_library(MATH_LIBRARY m)

link_libraries( ${MATH_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )


add_compile_options(-std=gnu17 -Wall -Wextra -Wconversion -Wpedantic)

add_executable(square_static square_static.c)
add_executable(square_dynamic square_dynamic.c)
add_executable(cube_static cube_static.c)
add_executable(cube_dynamic cube_dynamic.c)
