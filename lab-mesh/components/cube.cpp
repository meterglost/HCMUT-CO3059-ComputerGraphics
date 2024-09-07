#include "../main.hpp"

class Cube : public Mesh
{
public:
	Cube(const GLdouble size = 2.0)
	{
		this->vertices = {
			new Vertex(Point{ .x = -size / 2.0, .y = -size / 2.0, .z = -size / 2.0 }),
			new Vertex(Point{ .x = +size / 2.0, .y = -size / 2.0, .z = -size / 2.0 }),
			new Vertex(Point{ .x = +size / 2.0, .y = +size / 2.0, .z = -size / 2.0 }),
			new Vertex(Point{ .x = -size / 2.0, .y = +size / 2.0, .z = -size / 2.0 }),
			new Vertex(Point{ .x = -size / 2.0, .y = -size / 2.0, .z = +size / 2.0 }),
			new Vertex(Point{ .x = +size / 2.0, .y = -size / 2.0, .z = +size / 2.0 }),
			new Vertex(Point{ .x = +size / 2.0, .y = +size / 2.0, .z = +size / 2.0 }),
			new Vertex(Point{ .x = -size / 2.0, .y = +size / 2.0, .z = +size / 2.0 }),
		};

		this->faces = {
			new Face({ this->vertices[0], this->vertices[1], this->vertices[2], this->vertices[3] }, color[0]),
			new Face({ this->vertices[1], this->vertices[5], this->vertices[6], this->vertices[2] }, color[1]),
			new Face({ this->vertices[5], this->vertices[4], this->vertices[7], this->vertices[6] }, color[2]),
			new Face({ this->vertices[4], this->vertices[0], this->vertices[3], this->vertices[7] }, color[3]),
			new Face({ this->vertices[3], this->vertices[2], this->vertices[6], this->vertices[7] }, color[4]),
			new Face({ this->vertices[4], this->vertices[5], this->vertices[1], this->vertices[0] }, color[5]),
		};
	}
};

Cube object;
