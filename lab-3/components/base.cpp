#include "./base.hpp"

#include <GL/glut.h>

Object::Object()
{
}

Object::~Object()
{
	for (auto &vertex : this->vertices)
		delete vertex;
	for (auto &edge : this->edges)
		delete edge;
	for (auto &face : this->faces)
		delete face;

	for (auto &point : this->points)
		delete point;
	for (auto &normal : this->normals)
		delete normal;
}

void Object::draw_fill()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (auto &face : this->faces)
	{
		glNormal3d(face->normal->x, face->normal->y, face->normal->z);

		glBegin(GL_POLYGON);
		for (auto &vertex : face->points)
			glVertex3d(vertex->x, vertex->y, vertex->z);
		glEnd();
	}
}

void Object::draw_line()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glLineWidth(1.0F);
	glNormal3d(0.0, 0.0, 0.0);

	for (auto &face : this->faces)
	{
		glBegin(GL_POLYGON);
		for (auto &vertex : face->points)
			glVertex3d(vertex->x, vertex->y, vertex->z);
		glEnd();
	}
}
