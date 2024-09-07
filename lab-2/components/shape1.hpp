#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Shape1 : public Object
{
public:
	Shape1(GLdouble top_width, GLdouble bot_width, GLdouble height, GLdouble length);
};
