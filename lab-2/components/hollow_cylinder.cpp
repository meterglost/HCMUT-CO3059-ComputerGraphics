#include "./hollow_cylinder.hpp"

#include <cmath>

HollowCylinder::HollowCylinder(GLdouble const outer_radius, GLdouble const inner_radius, GLdouble const height, GLuint const slices)
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

	for (GLdouble angle = 0.0, delta = 2 * M_PI / slices; angle < 2 * M_PI; angle += delta)
	{
		this->points.push_back(new Point{ inner_radius * cos(angle), +height / 2, inner_radius * sin(angle) });
		this->points.push_back(new Point{ outer_radius * cos(angle), +height / 2, outer_radius * sin(angle) });
		this->points.push_back(new Point{ outer_radius * cos(angle), -height / 2, outer_radius * sin(angle) });
		this->points.push_back(new Point{ inner_radius * cos(angle), -height / 2, inner_radius * sin(angle) });
	}

	// Face

	for (GLuint i = 0; i < slices; ++i)
	{
		this->faces.push_back(new Face{
			{
				this->points[0 + (i + 0) * 4 % (4 * slices)],
				this->points[0 + (i + 1) * 4 % (4 * slices)],
				this->points[1 + (i + 1) * 4 % (4 * slices)],
				this->points[1 + (i + 0) * 4 % (4 * slices)],
			},
			this->colors[i % this->colors.size()],
		});

		this->faces.push_back(new Face{
			{
				this->points[1 + (i + 0) * 4 % (4 * slices)],
				this->points[1 + (i + 1) * 4 % (4 * slices)],
				this->points[2 + (i + 1) * 4 % (4 * slices)],
				this->points[2 + (i + 0) * 4 % (4 * slices)],
			},
			this->colors[i % this->colors.size()],
		});

		this->faces.push_back(new Face{
			{
				this->points[2 + (i + 0) * 4 % (4 * slices)],
				this->points[2 + (i + 1) * 4 % (4 * slices)],
				this->points[3 + (i + 1) * 4 % (4 * slices)],
				this->points[3 + (i + 0) * 4 % (4 * slices)],
			},
			this->colors[i % this->colors.size()],
		});

		this->faces.push_back(new Face{
			{
				this->points[0 + (i + 0) * 4 % (4 * slices)],
				this->points[0 + (i + 1) * 4 % (4 * slices)],
				this->points[3 + (i + 1) * 4 % (4 * slices)],
				this->points[3 + (i + 0) * 4 % (4 * slices)],
			},
			this->colors[i % this->colors.size()],
		});
	}
}

HollowCylinder object(1.0, 0.5, 2.0);
