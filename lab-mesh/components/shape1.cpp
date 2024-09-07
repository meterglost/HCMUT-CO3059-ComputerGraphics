#include "../main.hpp"

#include <cmath>

double deg2rad(const double degree)
{
	return degree * M_PI / 180.0;
}

class Shape1 : public Mesh
{
public:
	// Cone
	Shape1(const GLdouble radius = 2.0, const GLdouble height = 4.0, const GLuint slice = 10)
	{
		if (slice <= 2)
			throw("Slice must be greater than 2");

		this->vertices.push_back(new Vertex(Point{ 0.0, height / 2.0, 0.0 }));

		for (size_t i = 0; i < slice; i++)
		{
			GLdouble angle = 360.0 * (GLdouble)(i / slice);

			GLdouble x = radius * sin(deg2rad(angle));
			GLdouble y = -height / 2.0;
			GLdouble z = radius * cos(deg2rad(angle));

			this->vertices.push_back(new Vertex(Point{ x, y, z }));
		}

		for (size_t i = 0; i < slice; i++)
		{
			this->faces.push_back(new Face(
				{
					this->vertices[0],
					this->vertices[1 + (i + 0) % slice],
					this->vertices[1 + (i + 1) % slice],
				},
				color[i % color.size()]
			));
		}
	}
};

Shape1 object;
