#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Linker : public Object
{
public:
	Linker(GLdouble const width, GLdouble const height, GLdouble const length);
};
