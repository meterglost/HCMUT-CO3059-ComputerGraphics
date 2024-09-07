#include "./rail.hpp"

#include <cmath>

Rail::Rail(
	GLdouble const inner_width, GLdouble const inner_height,
	GLdouble const outer_width, GLdouble const outer_height,
	GLdouble const length
)
{
	if (inner_width <= 0.0 || outer_width <= inner_width)
		throw("invalid width");

	if (inner_height <= 0.0 || outer_height <= inner_height)
		throw("invalid height");

	if (length <= outer_width)
		throw("invalid length");

	for (GLdouble angle : { M_PI * 0 / 2, M_PI * 1 / 2, M_PI * 2 / 2, M_PI * 3 / 2 })
	{
		size_t pad1 = this->points.size();

		//

		this->points.push_back(new Point{ 0.0, 0.0, 0.0 });

		//

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + inner_width / 2 * +cos(angle),
			0.0,
			inner_width / 2 * +cos(angle) + inner_width / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + length / 2 * +cos(angle),
			0.0,
			inner_width / 2 * +cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * -sin(angle) + length / 2 * +cos(angle),
			0.0,
			inner_width / 2 * -cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * -sin(angle) + inner_width / 2 * +cos(angle),
			0.0,
			inner_width / 2 * -cos(angle) + inner_width / 2 * -sin(angle),
		});

		//

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + inner_width / 2 * +cos(angle),
			inner_height,
			inner_width / 2 * +cos(angle) + inner_width / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + length / 2 * +cos(angle),
			inner_height,
			inner_width / 2 * +cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * -sin(angle) + length / 2 * +cos(angle),
			inner_height,
			inner_width / 2 * -cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			inner_width / 2 * -sin(angle) + inner_width / 2 * +cos(angle),
			inner_height,
			inner_width / 2 * -cos(angle) + inner_width / 2 * -sin(angle),
		});

		//

		size_t pad2 = this->points.size();

		//

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + outer_width / 2 * +cos(angle),
			inner_height,
			outer_width / 2 * +cos(angle) + outer_width / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + length / 2 * +cos(angle),
			inner_height,
			outer_width / 2 * +cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * -sin(angle) + length / 2 * +cos(angle),
			inner_height,
			outer_width / 2 * -cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * -sin(angle) + outer_width / 2 * +cos(angle),
			inner_height,
			outer_width / 2 * -cos(angle) + outer_width / 2 * -sin(angle),
		});

		//

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + outer_width / 2 * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * +cos(angle) + outer_width / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + length / 2 * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * +cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * -sin(angle) + length / 2 * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * -cos(angle) + length / 2 * -sin(angle),
		});

		this->points.push_back(new Point{
			outer_width / 2 * -sin(angle) + outer_width / 2 * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * -cos(angle) + outer_width / 2 * -sin(angle),
		});

		//

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 0],
				this->points[pad1 + 1],
				this->points[pad1 + 2],
				this->points[pad1 + 3],
				this->points[pad1 + 4],
			},
			new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 1],
				this->points[pad1 + 2],
				this->points[pad1 + 6],
				this->points[pad1 + 5],
			},
			new Point{ -sin(angle), 0.0, -cos(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 3],
				this->points[pad1 + 4],
				this->points[pad1 + 8],
				this->points[pad1 + 7],
			},
			new Point{ +sin(angle), 0.0, +cos(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 5],
				this->points[pad1 + 6],
				this->points[pad2 + 1],
				this->points[pad2 + 0],
			},
			new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 7],
				this->points[pad1 + 8],
				this->points[pad2 + 3],
				this->points[pad2 + 2],
			},
			new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad2 + 0],
				this->points[pad2 + 1],
				this->points[pad2 + 5],
				this->points[pad2 + 4],
			},
			new Point{ +sin(angle), 0.0, +cos(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad2 + 2],
				this->points[pad2 + 3],
				this->points[pad2 + 7],
				this->points[pad2 + 6],
			},
			new Point{ -sin(angle), 0.0, -cos(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad2 + 4],
				this->points[pad2 + 5],
				this->points[pad2 + 6],
				this->points[pad2 + 7],
			},
			new Point{ 0.0, -1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 2],
				this->points[pad1 + 6],
				this->points[pad2 + 1],
				this->points[pad2 + 5],
			},
			new Point{ +cos(angle), 0.0, -sin(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad1 + 2],
				this->points[pad2 + 5],
				this->points[pad2 + 6],
				this->points[pad1 + 3],
			},
			new Point{ +cos(angle), 0.0, -sin(angle) },
		});

		this->faces.push_back(new Face{
			{
				this->points[pad2 + 6],
				this->points[pad2 + 2],
				this->points[pad1 + 7],
				this->points[pad1 + 3],
			},
			new Point{ +cos(angle), 0.0, -sin(angle) },
		});
	}

	for (auto &face : this->faces)
		this->normals.push_back(face->normal);
}
