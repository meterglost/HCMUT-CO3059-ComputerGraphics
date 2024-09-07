#include "./shape1.hpp"

Shape1::Shape1(GLdouble top_width, GLdouble bot_width, GLdouble height, GLdouble length)
{
	this->colors = {
		new Color{ 1.0, 0.0, 0.0 },
		new Color{ 0.0, 1.0, 0.0 },
		new Color{ 0.0, 0.0, 1.0 },
		new Color{ 1.0, 1.0, 0.0 },
		new Color{ 1.0, 0.0, 1.0 },
		new Color{ 0.0, 1.0, 1.0 },
	};

	this->points = {
		new Point{ -length / 2, +height / 2, -top_width / 2 },
		new Point{ -length / 2, +height / 2, +top_width / 2 },
		new Point{ -length / 2, -height / 2, +bot_width / 2 },
		new Point{ -length / 2, -height / 2, -bot_width / 2 },
		new Point{ +length / 2, +height / 2, -top_width / 2 },
		new Point{ +length / 2, +height / 2, +top_width / 2 },
		new Point{ +length / 2, -height / 2, +bot_width / 2 },
		new Point{ +length / 2, -height / 2, -bot_width / 2 },
	};

	this->faces = {
		new Face{
			{
				this->points[0],
				this->points[1],
				this->points[2],
				this->points[3],
			},
			this->colors[0],
		},
		new Face{
			{
				this->points[4],
				this->points[5],
				this->points[6],
				this->points[7],
			},
			this->colors[1],
		},
		new Face{
			{
				this->points[2],
				this->points[3],
				this->points[7],
				this->points[6],
			},
			this->colors[2],
		},
		new Face{
			{
				this->points[1],
				this->points[2],
				this->points[6],
				this->points[5],
			},
			this->colors[3],
		},
		new Face{
			{
				this->points[0],
				this->points[3],
				this->points[7],
				this->points[4],
			},
			this->colors[4],
		},
		new Face{
			{
				this->points[0],
				this->points[1],
				this->points[5],
				this->points[4],
			},
			this->colors[5],
		},
	};
}

Shape1 object(0.5, 1.0, 0.5, 2.0);
