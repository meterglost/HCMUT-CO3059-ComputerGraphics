#include "./tile.hpp"

Tile::Tile(GLdouble size)
{
	this->faces.push_back(new Face{
		.points = {
			new Point{ -size * 2 / 4, 0.0, +size * 2 / 4 },
			new Point{ -size * 1 / 4, 0.0, +size * 2 / 4 },
			new Point{ -size * 1 / 4, 0.0, +size * 1 / 4 },
			new Point{ -size * 2 / 4, 0.0, +size * 1 / 4 },
		},
		.color = new Color{ 1.0, 0.5, 0.5 },
	});

	this->faces.push_back(new Face{
		.points = {
			new Point{ +size * 2 / 4, 0.0, -size * 2 / 4 },
			new Point{ +size * 1 / 4, 0.0, -size * 2 / 4 },
			new Point{ +size * 1 / 4, 0.0, -size * 1 / 4 },
			new Point{ +size * 2 / 4, 0.0, -size * 1 / 4 },
		},
		.color = new Color{ 1.0, 0.5, 0.5 },
	});

	this->faces.push_back(new Face{
		.points = {
			new Point{ -size * 1 / 4, 0.0, +size * 1 / 4 },
			new Point{ -size * 2 / 4, 0.0, +size * 0 / 4 },
			new Point{ -size * 2 / 4, 0.0, -size * 2 / 4 },
			new Point{ -size * 1 / 4, 0.0, -size * 1 / 4 },
		},
		.color = new Color{ 0.5, 0.5, 1.0 },
	});

	this->faces.push_back(new Face{
		.points = {
			new Point{ -size * 1 / 4, 0.0, +size * 1 / 4 },
			new Point{ -size * 0 / 4, 0.0, +size * 2 / 4 },
			new Point{ +size * 2 / 4, 0.0, +size * 2 / 4 },
			new Point{ +size * 1 / 4, 0.0, +size * 1 / 4 },
		},
		.color = new Color{ 0.5, 0.5, 0.5 },
	});

	this->faces.push_back(new Face{
		.points = {
			new Point{ +size * 1 / 4, 0.0, -size * 1 / 4 },
			new Point{ +size * 2 / 4, 0.0, -size * 0 / 4 },
			new Point{ +size * 2 / 4, 0.0, +size * 2 / 4 },
			new Point{ +size * 1 / 4, 0.0, +size * 1 / 4 },
		},
		.color = new Color{ 0.5, 0.5, 1.0 },
	});

	this->faces.push_back(new Face{
		.points = {
			new Point{ +size * 1 / 4, 0.0, -size * 1 / 4 },
			new Point{ +size * 0 / 4, 0.0, -size * 2 / 4 },
			new Point{ -size * 2 / 4, 0.0, -size * 2 / 4 },
			new Point{ -size * 1 / 4, 0.0, -size * 1 / 4 },
		},
		.color = new Color{ 0.5, 0.5, 0.5 },
	});

	for (auto &face : this->faces)
	{
		this->points.push_back(face->points[0]);
		this->points.push_back(face->points[1]);
		this->points.push_back(face->points[2]);
		this->points.push_back(face->points[3]);

		this->colors.push_back(face->color);
	}
}
