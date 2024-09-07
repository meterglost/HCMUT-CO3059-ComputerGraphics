#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class SlidebarX : public Object
{
public:
	SlidebarX(GLdouble const width, GLdouble const height, GLdouble const length);
};

class SlidebarZ : public Object
{
public:
	SlidebarZ(GLdouble const width, GLdouble const height, GLdouble const length);
};
