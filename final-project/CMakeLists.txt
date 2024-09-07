cmake_minimum_required(VERSION 3.20.0)
project(final-project VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

find_library(MATH_LIBRARY m)

link_libraries( ${MATH_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )


add_executable(main main.cpp components/base.cpp components/tile.cpp components/rail.cpp)
