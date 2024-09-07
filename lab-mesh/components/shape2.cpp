#include "../main.hpp"

#include <cmath>

double deg2rad(const double degree)
{
	return degree * M_PI / 180.0;
}

class Shape2 : public Mesh
{
public:
	// Howlow cube
	Shape2(const GLdouble cube_size = 3.0, const GLdouble cylinder_size = 2.0, const GLuint slice = 16)
	{
		if (slice <= 0 || slice % 8 != 0)
			throw("Slice must be a multiple of 8");

		for (GLdouble angle = -45.0, delta = 360.0 / slice; angle < 360.0 - 45.0; angle += delta)
		{
			GLdouble x = cylinder_size / 2.0 * cos(deg2rad(angle));
			GLdouble y = cube_size / 2.0;
			GLdouble z = cylinder_size / 2.0 * sin(deg2rad(angle));

			this->vertices.push_back(new Vertex(Point{ x, +y, z }));
			this->vertices.push_back(new Vertex(Point{ x, -y, z }));
		}

		for (GLdouble angle = -45.0, delta = 360.0 / slice; angle < 360.0 - 45.0; angle += delta)
		{
			GLdouble x, y, z;

			if (-45.0 + 90.0 * 0 <= angle && angle < 45.0 + 90.0 * 0)
			{
				x = +cube_size / 2.0;
				y = +cube_size / 2.0;
				z = -cube_size / 2.0 + (angle + 45.0 - 90.0 * 0) / 90.0 * cube_size;
			}
			else if (-45.0 + 90.0 * 1 <= angle && angle < 45.0 + 90.0 * 1)
			{
				z = +cube_size / 2.0;
				y = +cube_size / 2.0;
				x = +cube_size / 2.0 - (angle + 45.0 - 90.0 * 1) / 90.0 * cube_size;
			}
			else if (-45.0 + 90.0 * 2 <= angle && angle < 45.0 + 90.0 * 2)
			{
				x = -cube_size / 2.0;
				y = +cube_size / 2.0;
				z = +cube_size / 2.0 - (angle + 45.0 - 90.0 * 2) / 90.0 * cube_size;
			}
			else if (-45.0 + 90.0 * 3 <= angle && angle < 45.0 + 90.0 * 3)
			{
				z = -cube_size / 2.0;
				y = +cube_size / 2.0;
				x = -cube_size / 2.0 + (angle + 45.0 - 90.0 * 3) / 90.0 * cube_size;
			}
			else
			{
				break;
			}

			this->vertices.push_back(new Vertex(Point{ x, +y, z }));
			this->vertices.push_back(new Vertex(Point{ x, -y, z }));
		}

		for (size_t idx = 0, len = slice; idx < len; ++idx)
		{
			const size_t pad_x = 0 * slice + 0, gap_x = 2;
			const size_t pad_y = 0 * slice + 1, gap_y = 2;

			this->faces.push_back(new Face(
				{
					this->vertices[pad_x + (idx + 0) % len * gap_x],
					this->vertices[pad_y + (idx + 0) % len * gap_y],
					this->vertices[pad_y + (idx + 1) % len * gap_y],
					this->vertices[pad_x + (idx + 1) % len * gap_x],
				},
				color[idx % color.size()]
			));
		}

		for (size_t idx = 0, len = slice; idx < len; ++idx)
		{
			const size_t pad_x = 0 * slice + 0, gap_x = 2;
			const size_t pad_y = 2 * slice + 0, gap_y = 2;

			this->faces.push_back(new Face(
				{
					this->vertices[pad_x + (idx + 0) % len * gap_x],
					this->vertices[pad_y + (idx + 0) % len * gap_y],
					this->vertices[pad_y + (idx + 1) % len * gap_y],
					this->vertices[pad_x + (idx + 1) % len * gap_x],
				},
				color[idx % color.size()]
			));
		}

		for (size_t idx = 0, len = slice; idx < len; ++idx)
		{
			const size_t pad_x = 0 * slice + 1, gap_x = 2;
			const size_t pad_y = 2 * slice + 1, gap_y = 2;

			this->faces.push_back(new Face(
				{
					this->vertices[pad_x + (idx + 0) % len * gap_x],
					this->vertices[pad_y + (idx + 0) % len * gap_y],
					this->vertices[pad_y + (idx + 1) % len * gap_y],
					this->vertices[pad_x + (idx + 1) % len * gap_x],
				},
				color[idx % color.size()]
			));
		}

		for (size_t idx = 0, len = 4; idx < len; ++idx)
		{
			const size_t pad_x = 2 * slice + 0, gap_x = 2 * slice / len;
			const size_t pad_y = 2 * slice + 1, gap_y = 2 * slice / len;

			this->faces.push_back(new Face(
				{
					this->vertices[pad_x + (idx + 0) % len * gap_x],
					this->vertices[pad_y + (idx + 0) % len * gap_y],
					this->vertices[pad_y + (idx + 1) % len * gap_y],
					this->vertices[pad_x + (idx + 1) % len * gap_x],
				},
				color[idx % color.size()]
			));
		}
	}

	~Shape2()
	{
	}
};

Shape2 object;
