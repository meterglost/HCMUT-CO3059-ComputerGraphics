#include "./linker.hpp"

#include <cmath>

Linker::Linker(GLdouble const width, GLdouble const height, GLdouble const length)
{
	this->points = {
		new Point{ -length / 2, height, -width / 2 },
		new Point{ -length / 2, height, +width / 2 },
		new Point{ +length / 2, height, +width / 2 },
		new Point{ +length / 2, height, -width / 2 },

		new Point{ -length / 2, height * 1.5, -width / 2 },
		new Point{ -length / 2, height * 1.5, +width / 2 },
		new Point{ +length / 2, height * 1.5, +width / 2 },
		new Point{ +length / 2, height * 1.5, -width / 2 },
	};

	this->faces = {
		new Face{ { this->points[0], this->points[1], this->points[2], this->points[3] }, new Point{ 0.0, -1.0, 0.0 } },
		new Face{ { this->points[4], this->points[5], this->points[6], this->points[7] }, new Point{ 0.0, +1.0, 0.0 } },
		new Face{ { this->points[0], this->points[1], this->points[5], this->points[4] }, new Point{ -1.0, 0.0, 0.0 } },
		new Face{ { this->points[1], this->points[2], this->points[6], this->points[5] }, new Point{ 0.0, 0.0, +1.0 } },
		new Face{ { this->points[2], this->points[3], this->points[7], this->points[6] }, new Point{ +1.0, 0.0, 0.0 } },
		new Face{ { this->points[3], this->points[0], this->points[4], this->points[7] }, new Point{ 0.0, 0.0, -1.0 } },
	};

	size_t slice = 10;

	size_t pad = this->points.size();

	for (GLdouble angle = 0.0, delta = M_PI / (GLdouble)slice; angle <= M_PI; angle += delta)
		this->points.push_back(new Point{ -length / 2 - width / 2 * sin(angle), height, width / 2 * cos(angle) });

	for (GLdouble angle = 0.0, delta = M_PI / (GLdouble)slice; angle <= M_PI; angle += delta)
		this->points.push_back(new Point{ -length / 2 - width / 2 * sin(angle), height * 1.5, width / 2 * cos(angle) });

	for (GLdouble angle = 0.0, delta = M_PI / (GLdouble)slice; angle <= M_PI; angle += delta)
		this->points.push_back(new Point{ +length / 2 + width / 2 * sin(angle), height, width / 2 * cos(angle) });

	for (GLdouble angle = 0.0, delta = M_PI / (GLdouble)slice; angle <= M_PI; angle += delta)
		this->points.push_back(new Point{ +length / 2 + width / 2 * sin(angle), height * 1.5, width / 2 * cos(angle) });

	for (size_t idx = 0; idx < slice; ++idx)
		this->faces.push_back(new Face{
			{
				this->points[pad + 0 * (slice + 1) + idx],
				this->points[pad + 0 * (slice + 1) + idx + 1],
				this->points[pad + 1 * (slice + 1) + idx + 1],
				this->points[pad + 1 * (slice + 1) + idx],
			},
			new Point{ 0.0, 1.0, 0.0 },
		});

	for (size_t idx = 0; idx < slice; ++idx)
		this->faces.push_back(new Face{
			{
				this->points[pad + 2 * (slice + 1) + idx],
				this->points[pad + 2 * (slice + 1) + idx + 1],
				this->points[pad + 3 * (slice + 1) + idx + 1],
				this->points[pad + 3 * (slice + 1) + idx],
			},
			new Point{ 0.0, 1.0, 0.0 },
		});

	this->faces.push_back(new Face{ {}, new Point{ 0.0, 1.0, 0.0 } });
	for (size_t idx = 0; idx <= slice; ++idx)
		this->faces.back()->points.push_back(this->points[pad + 1 * (slice + 1) + idx]);

	this->faces.push_back(new Face{ {}, new Point{ 0.0, 1.0, 0.0 } });
	for (size_t idx = 0; idx <= slice; ++idx)
		this->faces.back()->points.push_back(this->points[pad + 3 * (slice + 1) + idx]);

	for (auto &face : this->faces)
		this->normals.push_back(face->normal);
}
