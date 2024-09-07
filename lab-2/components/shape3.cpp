#include "./shape3.hpp"

Shape3::Shape3(GLdouble const size, GLdouble const length)
{
	if (size <= 0.0 || length <= 0.0 || length <= size)
		throw("invalid size or length");

	GLdouble const height      = size / 3 * 2;
	GLdouble const inner_width = size / 3;
	GLdouble const outer_width = size;

	this->colors = {
		new Color{ 0.6, 0.6, 0.6 },
		new Color{ 0.6, 0.3, 0.3 },
	};

	size_t pad1, pad2;

	// X bar

	pad1 = this->points.size();

	this->points.push_back(new Point{ -length, 0.0, -inner_width / 2 });
	this->points.push_back(new Point{ -length, 0.0, +inner_width / 2 });
	this->points.push_back(new Point{ +length, 0.0, +inner_width / 2 });
	this->points.push_back(new Point{ +length, 0.0, -inner_width / 2 });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -length, -height / 2, -inner_width / 2 });
	this->points.push_back(new Point{ -length, -height / 2, +inner_width / 2 });
	this->points.push_back(new Point{ +length, -height / 2, +inner_width / 2 });
	this->points.push_back(new Point{ +length, -height / 2, -inner_width / 2 });

	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad1 + 3] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad2 + 0], this->points[pad2 + 1], this->points[pad2 + 2], this->points[pad2 + 3] },
		this->colors[0],
	});

	for (size_t i = 0; i < 4; i++)
	{
		this->faces.push_back(new Face{
			{ this->points[pad1 + i], this->points[pad1 + (i + 1) % 4], this->points[pad2 + (i + 1) % 4], this->points[pad2 + i] },
			this->colors[0],
		});
	}

	// Z bar

	pad1 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, 0.0, -length });
	this->points.push_back(new Point{ +inner_width / 2, 0.0, -length });
	this->points.push_back(new Point{ +inner_width / 2, 0.0, +length });
	this->points.push_back(new Point{ -inner_width / 2, 0.0, +length });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, -height / 2, -length });
	this->points.push_back(new Point{ +inner_width / 2, -height / 2, -length });
	this->points.push_back(new Point{ +inner_width / 2, -height / 2, +length });
	this->points.push_back(new Point{ -inner_width / 2, -height / 2, +length });

	this->faces.push_back(new Face{
		{ this->points[pad1 + 0], this->points[pad1 + 1], this->points[pad1 + 2], this->points[pad1 + 3] },
		this->colors[0],
	});
	this->faces.push_back(new Face{
		{ this->points[pad2 + 0], this->points[pad2 + 1], this->points[pad2 + 2], this->points[pad2 + 3] },
		this->colors[0],
	});

	for (size_t idx = 0, len = 4; idx < len; idx++)
	{
		this->faces.push_back(new Face{
			{
				this->points[pad1 + idx],
				this->points[pad1 + (idx + 1) % len],
				this->points[pad2 + (idx + 1) % len],
				this->points[pad2 + idx],
			},
			this->colors[0],
		});
	}

	// +X-Z

	pad1 = this->points.size();

	this->points.push_back(new Point{ +inner_width / 2, -height / 2, -inner_width / 2 });

	this->points.push_back(new Point{ +length, -height / 2, -inner_width / 2 });
	this->points.push_back(new Point{ +length, -height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ +outer_width / 2, -height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ +outer_width / 2, -height / 2, -length });
	this->points.push_back(new Point{ +inner_width / 2, -height / 2, -length });

	pad2 = this->points.size();

	this->points.push_back(new Point{ +inner_width / 2, +height / 2, -inner_width / 2 });

	this->points.push_back(new Point{ +length, +height / 2, -inner_width / 2 });
	this->points.push_back(new Point{ +length, +height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ +outer_width / 2, +height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ +outer_width / 2, +height / 2, -length });
	this->points.push_back(new Point{ +inner_width / 2, +height / 2, -length });

	this->faces.push_back(new Face{
		{
			this->points[pad1 + 0],
			this->points[pad1 + 1],
			this->points[pad1 + 2],
			this->points[pad1 + 3],
			this->points[pad1 + 4],
			this->points[pad1 + 5],
		},
		this->colors[1],
	});
	this->faces.push_back(new Face{
		{
			this->points[pad2 + 0],
			this->points[pad2 + 1],
			this->points[pad2 + 2],
			this->points[pad2 + 3],
			this->points[pad2 + 4],
			this->points[pad2 + 5],
		},
		this->colors[1],
	});

	for (size_t idx = 0, len = 6; idx < len; idx++)
	{
		this->faces.push_back(new Face{
			{
				this->points[pad1 + idx],
				this->points[pad1 + (idx + 1) % len],
				this->points[pad2 + (idx + 1) % len],
				this->points[pad2 + idx],
			},
			this->colors[1],
		});
	}

	// -X-Z

	pad1 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, -height / 2, -inner_width / 2 });

	this->points.push_back(new Point{ -inner_width / 2, -height / 2, -length });
	this->points.push_back(new Point{ -outer_width / 2, -height / 2, -length });

	this->points.push_back(new Point{ -outer_width / 2, -height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ -length, -height / 2, -outer_width / 2 });
	this->points.push_back(new Point{ -length, -height / 2, -inner_width / 2 });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, +height / 2, -inner_width / 2 });

	this->points.push_back(new Point{ -inner_width / 2, +height / 2, -length });
	this->points.push_back(new Point{ -outer_width / 2, +height / 2, -length });

	this->points.push_back(new Point{ -outer_width / 2, +height / 2, -outer_width / 2 });

	this->points.push_back(new Point{ -length, +height / 2, -outer_width / 2 });
	this->points.push_back(new Point{ -length, +height / 2, -inner_width / 2 });

	this->faces.push_back(new Face{
		{
			this->points[pad1 + 0],
			this->points[pad1 + 1],
			this->points[pad1 + 2],
			this->points[pad1 + 3],
			this->points[pad1 + 4],
			this->points[pad1 + 5],
		},
		this->colors[1],
	});
	this->faces.push_back(new Face{
		{
			this->points[pad2 + 0],
			this->points[pad2 + 1],
			this->points[pad2 + 2],
			this->points[pad2 + 3],
			this->points[pad2 + 4],
			this->points[pad2 + 5],
		},
		this->colors[1],
	});

	for (size_t idx = 0, len = 6; idx < len; idx++)
	{
		this->faces.push_back(new Face{
			{
				this->points[pad1 + idx],
				this->points[pad1 + (idx + 1) % len],
				this->points[pad2 + (idx + 1) % len],
				this->points[pad2 + idx],
			},
			this->colors[1],
		});
	}

	// -X+Z

	pad1 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, -height / 2, +inner_width / 2 });

	this->points.push_back(new Point{ -length, -height / 2, +inner_width / 2 });
	this->points.push_back(new Point{ -length, -height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ -outer_width / 2, -height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ -outer_width / 2, -height / 2, +length });
	this->points.push_back(new Point{ -inner_width / 2, -height / 2, +length });

	pad2 = this->points.size();

	this->points.push_back(new Point{ -inner_width / 2, +height / 2, +inner_width / 2 });

	this->points.push_back(new Point{ -length, +height / 2, +inner_width / 2 });
	this->points.push_back(new Point{ -length, +height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ -outer_width / 2, +height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ -outer_width / 2, +height / 2, +length });
	this->points.push_back(new Point{ -inner_width / 2, +height / 2, +length });

	this->faces.push_back(new Face{
		{
			this->points[pad1 + 0],
			this->points[pad1 + 1],
			this->points[pad1 + 2],
			this->points[pad1 + 3],
			this->points[pad1 + 4],
			this->points[pad1 + 5],
		},
		this->colors[1],
	});
	this->faces.push_back(new Face{
		{
			this->points[pad2 + 0],
			this->points[pad2 + 1],
			this->points[pad2 + 2],
			this->points[pad2 + 3],
			this->points[pad2 + 4],
			this->points[pad2 + 5],
		},
		this->colors[1],
	});

	for (size_t idx = 0, len = 6; idx < len; idx++)
	{
		this->faces.push_back(new Face{
			{
				this->points[pad1 + idx],
				this->points[pad1 + (idx + 1) % len],
				this->points[pad2 + (idx + 1) % len],
				this->points[pad2 + idx],
			},
			this->colors[1],
		});
	}

	// +X+Z

	pad1 = this->points.size();

	this->points.push_back(new Point{ +inner_width / 2, -height / 2, +inner_width / 2 });

	this->points.push_back(new Point{ +inner_width / 2, -height / 2, +length });
	this->points.push_back(new Point{ +outer_width / 2, -height / 2, +length });

	this->points.push_back(new Point{ +outer_width / 2, -height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ +length, -height / 2, +outer_width / 2 });
	this->points.push_back(new Point{ +length, -height / 2, +inner_width / 2 });

	pad2 = this->points.size();

	this->points.push_back(new Point{ +inner_width / 2, +height / 2, +inner_width / 2 });

	this->points.push_back(new Point{ +inner_width / 2, +height / 2, +length });
	this->points.push_back(new Point{ +outer_width / 2, +height / 2, +length });

	this->points.push_back(new Point{ +outer_width / 2, +height / 2, +outer_width / 2 });

	this->points.push_back(new Point{ +length, +height / 2, +outer_width / 2 });
	this->points.push_back(new Point{ +length, +height / 2, +inner_width / 2 });

	this->faces.push_back(new Face{
		{
			this->points[pad1 + 0],
			this->points[pad1 + 1],
			this->points[pad1 + 2],
			this->points[pad1 + 3],
			this->points[pad1 + 4],
			this->points[pad1 + 5],
		},
		this->colors[1],
	});
	this->faces.push_back(new Face{
		{
			this->points[pad2 + 0],
			this->points[pad2 + 1],
			this->points[pad2 + 2],
			this->points[pad2 + 3],
			this->points[pad2 + 4],
			this->points[pad2 + 5],
		},
		this->colors[1],
	});

	for (size_t idx = 0, len = 6; idx < len; idx++)
	{
		this->faces.push_back(new Face{
			{
				this->points[pad1 + idx],
				this->points[pad1 + (idx + 1) % len],
				this->points[pad2 + (idx + 1) % len],
				this->points[pad2 + idx],
			},
			this->colors[1],
		});
	}
}

Shape3 object(0.6, 3.0);
