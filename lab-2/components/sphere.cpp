#include "./sphere.hpp"

#include <cmath>

Sphere::Sphere(GLdouble radius, GLuint slices)
	: Object()
{
	if (slices <= 0 || slices % 4 != 0)
		throw("Slices must be a multiple of 4");

	// Color

	GLdouble const delta_color = 0.5 / (slices / 4 - 1);

	for (size_t i = 0, len = slices / 4; i < len; ++i)
	{
		this->colors.push_back(new Color{
			.r = 0.5 + static_cast<GLdouble>(i) * delta_color,
			.g = 1.0,
			.b = 1.0 - static_cast<GLdouble>(i) * delta_color,
		});
	}

	for (size_t i = 0, len = slices / 4; i < len; ++i)
	{
		this->colors.push_back(new Color{
			.r = 1.0 - static_cast<GLdouble>(i) * delta_color,
			.g = 1.0,
			.b = 0.5 + static_cast<GLdouble>(i) * delta_color,
		});
	}

	// Point

	GLdouble const delta_radius = 2.0 * M_PI / slices;

	for (size_t i = 0, len = slices / 2; i <= len; ++i)
	{
		GLdouble const sub_radius = radius * std::sin(static_cast<GLdouble>(i) * delta_radius);
		GLdouble const y          = radius * std::cos(static_cast<GLdouble>(i) * delta_radius);

		for (size_t j = 0; j < slices; ++j)
		{
			GLdouble const x = sub_radius * std::sin(static_cast<GLdouble>(j) * delta_radius);
			GLdouble const z = sub_radius * std::cos(static_cast<GLdouble>(j) * delta_radius);

			this->points.push_back(new Point{ .x = x, .y = y, .z = z });
		}
	}

	// Face

	for (size_t i = 0, len = slices / 2; i < len; ++i)
	{
		for (size_t j = 0, len = slices; j < len; ++j)
		{
			const size_t pad_x = (i + 0) * slices, gap_x = 1;
			const size_t pad_y = (i + 1) * slices, gap_y = 1;

			this->faces.push_back(new Face{
				.points = {
					this->points[pad_x + (j + 0) % len * gap_x],
					this->points[pad_y + (j + 0) % len * gap_y],
					this->points[pad_y + (j + 1) % len * gap_y],
					this->points[pad_x + (j + 1) % len * gap_x],
				},
				.color = this->colors[i],
			});
		}
	}
}

Sphere object(2.0);
