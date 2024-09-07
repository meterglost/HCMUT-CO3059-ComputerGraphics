#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class HollowCylinder : public Object
{
public:
	HollowCylinder(GLdouble const outer_radius, GLdouble const inner_radius, GLdouble const height, GLuint const slices = 20);
};
