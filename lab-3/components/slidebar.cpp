#include "./slidebar.hpp"

SlidebarX::SlidebarX(GLdouble const width, GLdouble const height, GLdouble const length)
{
	this->points = {
		new Point{ -length / 2, 0.0, -width / 2 },
		new Point{ +length / 2, 0.0, -width / 2 },
		new Point{ +length / 2, 0.0, +width / 2 },
		new Point{ -length / 2, 0.0, +width / 2 },

		new Point{ -length / 2, height, -width / 2 },
		new Point{ +length / 2, height, -width / 2 },
		new Point{ +length / 2, height, +width / 2 },
		new Point{ -length / 2, height, +width / 2 },
	};

	this->faces.push_back(new Face{
		{
			this->points[0],
			this->points[1],
			this->points[2],
			this->points[3],
		},
		new Point{ 0.0, -1.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[4],
			this->points[5],
			this->points[6],
			this->points[7],
		},
		new Point{ 0.0, +1.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[0],
			this->points[1],
			this->points[5],
			this->points[4],
		},
		new Point{ 0.0, 0.0, -1.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[1],
			this->points[2],
			this->points[6],
			this->points[5],
		},
		new Point{ +1.0, 0.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[2],
			this->points[3],
			this->points[7],
			this->points[6],
		},
		new Point{ 0.0, 0.0, +1.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[3],
			this->points[0],
			this->points[4],
			this->points[7],
		},
		new Point{ -1.0, 0.0, 0.0 },
	});

	this->normals = {
		this->faces[0]->normal,
		this->faces[1]->normal,
		this->faces[2]->normal,
		this->faces[3]->normal,
		this->faces[4]->normal,
		this->faces[5]->normal,
	};
}

SlidebarZ::SlidebarZ(GLdouble const width, GLdouble const height, GLdouble const length)
{
	this->points = {
		new Point{ -width / 2, 0.0, -length / 2 },
		new Point{ +width / 2, 0.0, -length / 2 },
		new Point{ +width / 2, 0.0, +length / 2 },
		new Point{ -width / 2, 0.0, +length / 2 },

		new Point{ -width / 2, height, -length / 2 },
		new Point{ +width / 2, height, -length / 2 },
		new Point{ +width / 2, height, +length / 2 },
		new Point{ -width / 2, height, +length / 2 },
	};

	this->faces.push_back(new Face{
		{
			this->points[0],
			this->points[1],
			this->points[2],
			this->points[3],
		},
		new Point{ 0.0, -1.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[4],
			this->points[5],
			this->points[6],
			this->points[7],
		},
		new Point{ 0.0, +1.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[0],
			this->points[1],
			this->points[5],
			this->points[4],
		},
		new Point{ 0.0, 0.0, -1.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[1],
			this->points[2],
			this->points[6],
			this->points[5],
		},
		new Point{ +1.0, 0.0, 0.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[2],
			this->points[3],
			this->points[7],
			this->points[6],
		},
		new Point{ 0.0, 0.0, +1.0 },
	});

	this->faces.push_back(new Face{
		{
			this->points[3],
			this->points[0],
			this->points[4],
			this->points[7],
		},
		new Point{ -1.0, 0.0, 0.0 },
	});

	this->normals = {
		this->faces[0]->normal,
		this->faces[1]->normal,
		this->faces[2]->normal,
		this->faces[3]->normal,
		this->faces[4]->normal,
		this->faces[5]->normal,
	};
}
