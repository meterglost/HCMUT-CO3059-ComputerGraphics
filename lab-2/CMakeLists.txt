cmake_minimum_required(VERSION 3.20.0)
project(lab-2 VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_library(MATH_LIBRARY m)

link_libraries( ${MATH_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )


add_compile_options(-std=c++20 -Wall -Wextra -Wconversion -Wpedantic)

add_executable(Cube main.cpp components/base.cpp components/cube.cpp)
add_executable(Sphere main.cpp components/base.cpp components/sphere.cpp)
add_executable(Cylinder main.cpp components/base.cpp components/cylinder.cpp)
add_executable(HollowCylinder main.cpp components/base.cpp components/hollow_cylinder.cpp)

add_executable(Shape1 main.cpp components/base.cpp components/shape1.cpp)
add_executable(Shape2 main.cpp components/base.cpp components/shape2.cpp)
add_executable(Shape3 main.cpp components/base.cpp components/shape3.cpp)
