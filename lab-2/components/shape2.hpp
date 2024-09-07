#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Shape2 : public Object
{
public:
	Shape2(GLdouble r1, GLdouble r2, GLdouble r3, GLdouble width, GLdouble length, GLdouble height, GLuint slices = 10);
};
