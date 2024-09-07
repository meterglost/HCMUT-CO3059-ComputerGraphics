#include "./shape2.hpp"

#include <cmath>

Shape2::Shape2(GLdouble r1, GLdouble r2, GLdouble r3, GLdouble width, GLdouble length, GLdouble height, GLuint slices)
{
	this->colors = {
		new Color{ 1.0, 1.0, 1.0 },
	};

	size_t pad1, pad2;

	// Horizontal bar

	pad1 = this->points.size();

	this->points.push_back(new Point{ -width / 2, -height / 2, -r1 });
	this->points.push_back(new Point{ -width / 2, -height / 2, +r1 });
	this->points.push_back(new Point{ +width / 2, -height / 2, +r1 });
	this->points.push_back(new Point{ +width / 2, -height / 2, -r1 });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -width / 2, +height / 2, -r1 });
	this->points.push_back(new Point{ -width / 2, +height / 2, +r1 });
	this->points.push_back(new Point{ +width / 2, +height / 2, +r1 });
	this->points.push_back(new Point{ +width / 2, +height / 2, -r1 });

	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad1 + 3] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad2 + 0], this->points[pad2 + 1], this->points[pad2 + 2], this->points[pad2 + 3] },
		this->colors[0],
	});

	this->faces.push_back(new Face{
		{ this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad2 + 2], this->points[pad2 + 1] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 3], this->points[pad2 + 3], this->points[pad2 + 0] },
		this->colors[0],
	});

	// Vertical bar

	pad1 = this->points.size();

	this->points.push_back(new Point{ -r3, -height / 2, +r1 });
	this->points.push_back(new Point{ +r3, -height / 2, +r1 });
	this->points.push_back(new Point{ +r3, -height / 2, +r1 + length });
	this->points.push_back(new Point{ -r3, -height / 2, +r1 + length });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -r3, +height / 2, +r1 });
	this->points.push_back(new Point{ +r3, +height / 2, +r1 });
	this->points.push_back(new Point{ +r3, +height / 2, +r1 + length });
	this->points.push_back(new Point{ -r3, +height / 2, +r1 + length });

	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad1 + 3] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad2 + 0], this->points[pad2 + 1], this->points[pad2 + 2], this->points[pad2 + 3] },
		this->colors[0],
	});

	this->faces.push_back(new Face{
		{ this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad2 + 2], this->points[pad2 + 1] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 3], this->points[pad2 + 3], this->points[pad2 + 0] },
		this->colors[0],
	});

	// R1 left

	pad1 = this->points.size();

	this->points.push_back(new Point{ -width / 2, -height / 2, 0.0 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			-width / 2 - r1 * sin(angle),
			-height / 2,
			-r1 * cos(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + 0], this->points[pad1 + 1 + j], this->points[pad1 + 1 + j + 1] },
			this->colors[0],
		});
	}

	pad2 = this->points.size();

	this->points.push_back(new Point{ -width / 2, +height / 2, 0.0 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			-width / 2 - r1 * sin(angle),
			+height / 2,
			-r1 * cos(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad2 + 0], this->points[pad2 + 1 + j], this->points[pad2 + 1 + j + 1] },
			this->colors[0],
		});
	}

	for (GLuint j = 1; j <= slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + j], this->points[pad2 + j], this->points[pad2 + j + 1], this->points[pad1 + j + 1] },
			this->colors[0],
		});
	}

	// R1 right

	pad1 = this->points.size();

	this->points.push_back(new Point{ +width / 2, -height / 2, 0.0 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			+width / 2 + r1 * sin(angle),
			-height / 2,
			-r1 * cos(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + 0], this->points[pad1 + 1 + j], this->points[pad1 + 1 + j + 1] },
			this->colors[0],
		});
	}

	pad2 = this->points.size();

	this->points.push_back(new Point{ +width / 2, +height / 2, 0.0 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			+width / 2 + r1 * sin(angle),
			+height / 2,
			-r1 * cos(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad2 + 0], this->points[pad2 + 1 + j], this->points[pad2 + 1 + j + 1] },
			this->colors[0],
		});
	}

	for (GLuint j = 1; j <= slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + j], this->points[pad2 + j], this->points[pad2 + j + 1], this->points[pad1 + j + 1] },
			this->colors[0],
		});
	}

	// R2 left

	pad1 = this->points.size();

	this->points.push_back(new Point{ -r3, -height / 2, +r1 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI / 2 * j / slices;

		this->points.push_back(new Point{
			-r3 - r2 * (1 - cos(angle)),
			-height / 2,
			+r1 + r2 * (1 - sin(angle)),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + 0], this->points[pad1 + 1 + j], this->points[pad1 + 1 + j + 1] },
			this->colors[0],
		});
	}

	pad2 = this->points.size();

	this->points.push_back(new Point{ -r3, +height / 2, +r1 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI / 2 * j / slices;

		this->points.push_back(new Point{
			-r3 - r2 * (1 - cos(angle)),
			+height / 2,
			+r1 + r2 * (1 - sin(angle)),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad2 + 0], this->points[pad2 + 1 + j], this->points[pad2 + 1 + j + 1] },
			this->colors[0],
		});
	}

	for (GLuint j = 1; j <= slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + j], this->points[pad2 + j], this->points[pad2 + j + 1], this->points[pad1 + j + 1] },
			this->colors[0],
		});
	}

	// R2 right

	pad1 = this->points.size();

	this->points.push_back(new Point{ +r3, -height / 2, +r1 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI / 2 * j / slices;

		this->points.push_back(new Point{
			+r3 + r2 * (1 - cos(angle)),
			-height / 2,
			+r1 + r2 * (1 - sin(angle)),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + 0], this->points[pad1 + 1 + j], this->points[pad1 + 1 + j + 1] },
			this->colors[0],
		});
	}

	pad2 = this->points.size();

	this->points.push_back(new Point{ +r3, +height / 2, +r1 });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI / 2 * j / slices;

		this->points.push_back(new Point{
			+r3 + r2 * (1 - cos(angle)),
			+height / 2,
			+r1 + r2 * (1 - sin(angle)),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad2 + 0], this->points[pad2 + 1 + j], this->points[pad2 + 1 + j + 1] },
			this->colors[0],
		});
	}

	for (GLuint j = 1; j <= slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + j], this->points[pad2 + j], this->points[pad2 + j + 1], this->points[pad1 + j + 1] },
			this->colors[0],
		});
	}

	// R3

	pad1 = this->points.size();

	this->points.push_back(new Point{ 0.0, -height / 2, r1 + length });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			+r3 * cos(angle),
			-height / 2,
			+r1 + length + r3 * sin(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + 0], this->points[pad1 + 1 + j], this->points[pad1 + 1 + j + 1] },
			this->colors[0],
		});
	}

	pad2 = this->points.size();

	this->points.push_back(new Point{ 0.0, +height / 2, r1 + length });

	for (GLuint j = 0; j <= slices; j++)
	{
		GLdouble angle = M_PI * j / slices;

		this->points.push_back(new Point{
			+r3 * cos(angle),
			+height / 2,
			+r1 + length + r3 * sin(angle),
		});
	}

	for (GLuint j = 0; j < slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad2 + 0], this->points[pad2 + 1 + j], this->points[pad2 + 1 + j + 1] },
			this->colors[0],
		});
	}

	for (GLuint j = 1; j <= slices; j++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + j], this->points[pad2 + j], this->points[pad2 + j + 1], this->points[pad1 + j + 1] },
			this->colors[0],
		});
	}
}

Shape2 object(0.2, 0.2, 0.2, 2.0, 2.0, 0.2);
