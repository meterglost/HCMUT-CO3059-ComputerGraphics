#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Cylinder : public Object
{
public:
	Cylinder(GLdouble const radius, GLdouble const height, GLuint const slices = 20);
};
