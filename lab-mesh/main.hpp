#pragma once

#include <GL/glut.h>
#include <vector>

// -------------------------------------------------- //

typedef struct Color
{
	double r, g, b;
} Color;

typedef struct Point
{
	double x, y, z;
} Point;

// -------------------------------------------------- //

class Vertex
{
	friend class Mesh;

private:
	const Point point;
	const Color color;

public:
	Vertex(const Point point, const Color color = Color{})
		: point(point), color(color)
	{
	}
};

class Face
{
	friend class Mesh;

private:
	std::vector<const Vertex *> vertices;
	const Color color;

public:
	Face(std::vector<const Vertex *> const &vertices, const Color color)
		: vertices(vertices), color(color)
	{
	}
};

class Mesh
{
protected:
	std::vector<Vertex *> vertices;
	std::vector<Face *> faces;

public:
	Mesh() {};

	~Mesh()
	{
		for (auto face : faces)
			delete face;

		for (auto vertex : vertices)
			delete vertex;
	}

	void drawPoint()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glPointSize(3);

		glBegin(GL_POLYGON);
		for (auto vertex : vertices)
		{
			glColor3d(vertex->color.r, vertex->color.g, vertex->color.b);
			glVertex3d(vertex->point.x, vertex->point.y, vertex->point.z);
		}
		glEnd();
	}

	void drawLine()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1);

		for (auto face : faces)
		{
			glBegin(GL_POLYGON);
			for (auto vertex : face->vertices)
			{
				glColor3d(0.0, 0.0, 0.0);
				glVertex3d(vertex->point.x, vertex->point.y, vertex->point.z);
			}
			glEnd();
		}
	}

	void drawFace()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		for (auto face : faces)
		{
			glColor3d(face->color.r, face->color.g, face->color.b);
			glBegin(GL_POLYGON);
			for (auto vertex : face->vertices)
				glVertex3d(vertex->point.x, vertex->point.y, vertex->point.z);
			glEnd();
		}
	}
};

// -------------------------------------------------- //

static std::vector<Color> color = {
	Color{ .r = 1.0, .g = 0.0, .b = 0.0 },
	Color{ .r = 0.0, .g = 1.0, .b = 0.0 },
	Color{ .r = 0.0, .g = 0.0, .b = 1.0 },
	Color{ .r = 1.0, .g = 1.0, .b = 0.0 },
	Color{ .r = 1.0, .g = 0.0, .b = 1.0 },
	Color{ .r = 0.0, .g = 1.0, .b = 1.0 },
	Color{ .r = 0.3, .g = 0.3, .b = 0.3 },
	Color{ .r = 0.5, .g = 0.5, .b = 0.5 },
	Color{ .r = 0.9, .g = 0.9, .b = 0.9 },
	Color{ .r = 1.0, .g = 0.5, .b = 0.5 },
	Color{ .r = 0.5, .g = 1.0, .b = 0.5 },
	Color{ .r = 0.5, .g = 0.5, .b = 1.0 },
	Color{ .r = 0.0, .g = 0.0, .b = 0.0 },
	Color{ .r = 0.7, .g = 0.7, .b = 0.7 },
};
