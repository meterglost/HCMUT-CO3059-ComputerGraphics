#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Rail : public Object
{
public:
	Rail(
		GLdouble const inner_width, GLdouble const inner_height,
		GLdouble const outer_width, GLdouble const outer_height,
		GLdouble const length
	);
};
