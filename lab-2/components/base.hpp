#pragma once

#include <vector>

struct Color
{
	double r, g, b, a = 1.0;
};

struct Point
{
	double x, y, z;
};

struct Vertex
{
	Point *point;
	Color *color;
};

struct Edge
{
	Point *p1;
	Point *p2;
	Color *color;
};

struct Face
{
	std::vector<Point *> points;
	Color *color;
};

class Object
{
protected:
	std::vector<Point *> points;
	std::vector<Color *> colors;

protected:
	std::vector<Vertex *> vertices;
	std::vector<Edge *> edges;
	std::vector<Face *> faces;

public:
	Object();
	~Object();

	void draw_fill();
	void draw_line();
};
