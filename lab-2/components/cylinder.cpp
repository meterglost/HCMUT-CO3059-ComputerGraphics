#include "./cylinder.hpp"

#include <cmath>

Cylinder::Cylinder(GLdouble const radius, GLdouble const height, GLuint const slices)
{
	// Color

	this->colors = {
		new Color{ 1.0, 0.0, 0.0 },
		new Color{ 0.0, 1.0, 0.0 },
		new Color{ 0.0, 0.0, 1.0 },
		new Color{ 1.0, 1.0, 0.0 },
		new Color{ 1.0, 0.0, 1.0 },
		new Color{ 0.0, 1.0, 1.0 },
		new Color{ 0.2, 0.2, 0.2 },
		new Color{ 0.5, 0.5, 0.5 },
		new Color{ 0.8, 0.8, 0.8 },
		new Color{ 1.0, 0.5, 0.5 },
		new Color{ 0.5, 1.0, 0.5 },
		new Color{ 0.5, 0.5, 1.0 },
	};

	// Point

	this->points.push_back(new Point{ 0.0, +height / 2, 0.0 });
	this->points.push_back(new Point{ 0.0, -height / 2, 0.0 });

	for (GLdouble angle = 0.0, delta = 2 * M_PI / slices; angle < 2 * M_PI; angle += delta)
	{
		this->points.push_back(new Point{ radius * cos(angle), +height / 2, radius * sin(angle) });
		this->points.push_back(new Point{ radius * cos(angle), -height / 2, radius * sin(angle) });
	}

	// Face

	for (GLuint i = 0; i < slices; ++i)
	{
		this->faces.push_back(new Face{
			{
				this->points[0],
				this->points[2 + (i + 0) * 2 % (2 * slices)],
				this->points[2 + (i + 1) * 2 % (2 * slices)],
			},
			this->colors[i % this->colors.size()],
		});

		this->faces.push_back(new Face{
			{
				this->points[2 + (i + 0) * 2 % (2 * slices)],
				this->points[2 + (i + 1) * 2 % (2 * slices)],
				this->points[3 + (i + 1) * 2 % (2 * slices)],
				this->points[3 + (i + 0) * 2 % (2 * slices)],
			},
			this->colors[i % this->colors.size()],
		});

		this->faces.push_back(new Face{
			{
				this->points[1],
				this->points[3 + (i + 0) * 2 % (2 * slices)],
				this->points[3 + (i + 1) * 2 % (2 * slices)],
			},
			this->colors[i % this->colors.size()],
		});
	}
}

Cylinder object(1.0, 2.0);
