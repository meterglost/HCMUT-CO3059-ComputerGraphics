#include "./cube.hpp"

Cube::Cube(GLdouble const size)
{
	this->colors = {
		new Color{ .r = 1.0, .g = 0.5, .b = 0.5 },
		new Color{ .r = 0.5, .g = 1.0, .b = 0.5 },
		new Color{ .r = 0.5, .g = 0.5, .b = 1.0 },
	};

	this->points = {
		new Point{ .x = -size / 2, .y = -size / 2, .z = -size / 2 },
		new Point{ .x = -size / 2, .y = -size / 2, .z = +size / 2 },
		new Point{ .x = +size / 2, .y = -size / 2, .z = +size / 2 },
		new Point{ .x = +size / 2, .y = -size / 2, .z = -size / 2 },

		new Point{ .x = -size / 2, .y = +size / 2, .z = -size / 2 },
		new Point{ .x = -size / 2, .y = +size / 2, .z = +size / 2 },
		new Point{ .x = +size / 2, .y = +size / 2, .z = +size / 2 },
		new Point{ .x = +size / 2, .y = +size / 2, .z = -size / 2 },
	};

	this->faces = {
		new Face{ { points[0], points[1], points[2], points[3] }, colors[0] }, // Bottom
		new Face{ { points[4], points[5], points[6], points[7] }, colors[0] }, // Top
		new Face{ { points[0], points[1], points[5], points[4] }, colors[1] }, // Left
		new Face{ { points[2], points[3], points[7], points[6] }, colors[1] }, // Right
		new Face{ { points[1], points[2], points[6], points[5] }, colors[2] }, // Front
		new Face{ { points[0], points[3], points[7], points[4] }, colors[2] }, // Back
	};
}

Cube object(2.0);
