#pragma once

#include "./base.hpp"

#include <GL/glut.h>

class Sphere : public Object
{
public:
	Sphere(GLdouble radius, GLuint slices = 16);
};
