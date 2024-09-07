#include "./rail.hpp"

#include <cmath>

Rail::Rail(
	GLdouble const inner_width, GLdouble const inner_height,
	GLdouble const outer_width, GLdouble const outer_height,
	GLdouble const length,
	GLuint const nth_way
)
{
	if (inner_width <= 0.0 || outer_width <= inner_width)
		throw("invalid width");

	if (inner_height <= 0.0 || outer_height <= inner_height)
		throw("invalid height");

	if (length <= outer_width)
		throw("invalid length");

	GLdouble theta = tan(M_PI_2 - M_PI / (2 * nth_way));

	for (size_t idx = 0; idx < 2 * nth_way; ++idx)
	{
		GLdouble angle = M_PI * idx / nth_way;

		size_t pad1 = this->points.size();

		//

		this->points.push_back(new Point{ 0.0, 0.0, 0.0 });

		//

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + inner_width / 2 * theta * +cos(angle),
			0.0,
			inner_width / 2 * +cos(angle) + inner_width / 2 * theta * -sin(angle),
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
			inner_width / 2 * -sin(angle) + inner_width / 2 * theta * +cos(angle),
			0.0,
			inner_width / 2 * -cos(angle) + inner_width / 2 * theta * -sin(angle),
		});

		//

		this->points.push_back(new Point{
			inner_width / 2 * +sin(angle) + inner_width / 2 * theta * +cos(angle),
			inner_height,
			inner_width / 2 * +cos(angle) + inner_width / 2 * theta * -sin(angle),
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
			inner_width / 2 * -sin(angle) + inner_width / 2 * theta * +cos(angle),
			inner_height,
			inner_width / 2 * -cos(angle) + inner_width / 2 * theta * -sin(angle),
		});

		//

		size_t pad2 = this->points.size();

		//

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + outer_width / 2 * theta * +cos(angle),
			inner_height,
			outer_width / 2 * +cos(angle) + outer_width / 2 * theta * -sin(angle),
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
			outer_width / 2 * -sin(angle) + outer_width / 2 * theta * +cos(angle),
			inner_height,
			outer_width / 2 * -cos(angle) + outer_width / 2 * theta * -sin(angle),
		});

		//

		this->points.push_back(new Point{
			outer_width / 2 * +sin(angle) + outer_width / 2 * theta * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * +cos(angle) + outer_width / 2 * theta * -sin(angle),
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
			outer_width / 2 * -sin(angle) + outer_width / 2 * theta * +cos(angle),
			inner_height - outer_height,
			outer_width / 2 * -cos(angle) + outer_width / 2 * theta * -sin(angle),
		});

		this->points.push_back(new Point{ 0.0, inner_height - outer_height, 0.0 });

		//

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 0],
				this->points[pad1 + 1],
				this->points[pad1 + 2],
				this->points[pad1 + 3],
				this->points[pad1 + 4],
			},
			.normal = new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 1],
				this->points[pad1 + 2],
				this->points[pad1 + 6],
				this->points[pad1 + 5],
			},
			.normal = new Point{ -sin(angle), 0.0, -cos(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 3],
				this->points[pad1 + 4],
				this->points[pad1 + 8],
				this->points[pad1 + 7],
			},
			.normal = new Point{ +sin(angle), 0.0, +cos(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 5],
				this->points[pad1 + 6],
				this->points[pad2 + 1],
				this->points[pad2 + 0],
			},
			.normal = new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 7],
				this->points[pad1 + 8],
				this->points[pad2 + 3],
				this->points[pad2 + 2],
			},
			.normal = new Point{ 0.0, +1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad2 + 0],
				this->points[pad2 + 1],
				this->points[pad2 + 5],
				this->points[pad2 + 4],
			},
			.normal = new Point{ +sin(angle), 0.0, +cos(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad2 + 2],
				this->points[pad2 + 3],
				this->points[pad2 + 7],
				this->points[pad2 + 6],
			},
			.normal = new Point{ -sin(angle), 0.0, -cos(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad2 + 4],
				this->points[pad2 + 5],
				this->points[pad2 + 6],
				this->points[pad2 + 7],
				this->points[pad2 + 8],
			},
			.normal = new Point{ 0.0, -1.0, 0.0 },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 2],
				this->points[pad1 + 6],
				this->points[pad2 + 1],
				this->points[pad2 + 5],
			},
			.normal = new Point{ +cos(angle), 0.0, -sin(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad1 + 2],
				this->points[pad2 + 5],
				this->points[pad2 + 6],
				this->points[pad1 + 3],
			},
			.normal = new Point{ +cos(angle), 0.0, -sin(angle) },
		});

		this->faces.push_back(new Face{
			.points = {
				this->points[pad2 + 6],
				this->points[pad2 + 2],
				this->points[pad1 + 7],
				this->points[pad1 + 3],
			},
			.normal = new Point{ +cos(angle), 0.0, -sin(angle) },
		});
	}

	for (auto &face : this->faces)
		this->normals.push_back(face->normal);
}
