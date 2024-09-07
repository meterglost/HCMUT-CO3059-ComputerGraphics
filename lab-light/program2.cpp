#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_radius = 5.0;
GLdouble camera_height = 2.0;

// -------------------------------------------------- //

namespace Light
{
	typedef struct Type
	{
		const GLfloat ambient[4]  = {};
		const GLfloat diffuse[4]  = {};
		const GLfloat specular[4] = {};
		const GLfloat position[4] = {};
	} Type;

	enum Name
	{
		Left,
		Right,
	};
}

namespace Material
{
	typedef struct Type
	{
		const GLfloat ambient[4]   = {};
		const GLfloat diffuse[4]   = {};
		const GLfloat specular[4]  = {};
		const GLfloat shininess[1] = {};
	} Type;

	enum Name
	{
		Default,
	};
}

// -------------------------------------------------- //

void setLight()
{
	static std::map<Light::Name, Light::Type> lights = {
		{
			Light::Left,
			{
				.ambient  = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse  = { 1.0F, 0.0F, 0.0F, 1.0F },
				.specular = { 1.0F, 1.0F, 0.0F, 1.0F },
				.position = { -5.0F, 0.0F, 0.0F, 0.0F },

			},
		},
		{
			Light::Right,
			{
				.ambient  = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse  = { 0.0F, 0.0F, 1.0F, 1.0F },
				.specular = { 1.0F, 0.0F, 1.0F, 1.0F },
				.position = { 5.0F, 0.0F, 0.0F, 0.0F },
			},
		},
	};

	for (auto const &[idx, light] : lights)
	{
		glLightfv(GL_LIGHT0 + idx, GL_AMBIENT, light.ambient);
		glLightfv(GL_LIGHT0 + idx, GL_DIFFUSE, light.diffuse);
		glLightfv(GL_LIGHT0 + idx, GL_SPECULAR, light.specular);
		glLightfv(GL_LIGHT0 + idx, GL_POSITION, light.position);

		glEnable(GL_LIGHT0 + idx);
	}
}

void setCamera()
{
	glLoadIdentity();
	gluLookAt(camera_radius, camera_height, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void setMaterial(Material::Name name = Material::Default)
{
	static std::map<Material::Name, Material::Type> materials = {
		{
			Material::Default,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 1.0F, 1.0F, 1.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, materials[name].ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[name].diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materials[name].specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materials[name].shininess);
}

void glutConfig()
{
	setLight();
	setCamera();
	setMaterial();

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSolidSphere(2.0, 100, 100);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	const double VIRTUAL_WIDTH  = width / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = height / WINDOW_SCALE;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	const int WINDOW_WIDTH  = 1280;
	const int WINDOW_HEIGHT = 720;

	const int SCREEN_WIDTH  = glutGet(GLUT_SCREEN_WIDTH);
	const int SCREEN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);

	if (SCREEN_WIDTH < WINDOW_WIDTH || SCREEN_HEIGHT < WINDOW_HEIGHT)
		throw("Screen size is too small to run this program");

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	glutCreateWindow("Lab Light");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutConfig();
	glutMainLoop();
}
