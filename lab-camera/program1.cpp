#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_angle  = 0.0;
GLdouble camera_radius = 0.0;
GLdouble camera_height = -4.0;

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
		Light1,
		Light2,
		Light3,
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
			Light::Light1,
			{
				.diffuse  = { 1.0F, 0.0F, 0.0F, 1.0F },
				.position = { 10.0F, 10.0F, 20.0F, 0.0F },
			},
		},
		{
			Light::Light2,
			{
				.diffuse  = { 0.7F, 0.7F, 0.7F, 1.0F },
				.position = { 10.0F, 10.0F, -20.0F, 0.0F },
			},
		},
		{
			Light::Light3,
			{
				.diffuse  = { 0.7F, 0.7F, 0.7F, 1.0F },
				.position = { 0.0F, -10.0F, 0.0F, 0.0F },
			},
		},
	};

	for (auto const &[idx, light] : lights)
	{
		glLightfv(GL_LIGHT0 + idx, GL_DIFFUSE, light.diffuse);
		glLightfv(GL_LIGHT0 + idx, GL_POSITION, light.position);

		glEnable(GL_LIGHT0 + idx);
	}
}

void setCamera()
{
	glLoadIdentity();
	gluLookAt(0.0, camera_height, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
}

void setMaterial()
{
	static std::map<Material::Name, Material::Type> materials = {
		{
			Material::Default,
			{
				.ambient   = { 0.7F, 0.7F, 0.7F, 1.0F },
				.diffuse   = { 1.0F, 0.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 50.0F },
			},
		},
	};

	glMaterialfv(GL_FRONT, GL_AMBIENT, materials[Material::Default].ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[Material::Default].diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materials[Material::Default].specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, materials[Material::Default].shininess);
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

void drawAxis()
{
	GLdouble xmin = -3.0, xmax = 3.0;
	GLdouble ymin = -3.0, ymax = 3.0;
	GLdouble zmin = -3.0, zmax = 3.0;

	glColor3d(0.0, 0.0, 1.0);

	glBegin(GL_LINES);
	glVertex3d(xmin, 0.0, 0.0);
	glVertex3d(xmax, 0.0, 0.0);
	glVertex3d(0.0, ymin, 0.0);
	glVertex3d(0.0, ymax, 0.0);
	glVertex3d(0.0, 0.0, zmin);
	glVertex3d(0.0, 0.0, zmax);
	glEnd();

	void *font = GLUT_BITMAP_TIMES_ROMAN_24;

	glColor3d(0.0, 0.0, 0.0);

	glRasterPos3d(xmax, 0.0, 0.0);
	glutBitmapCharacter(font, 'X');
	glRasterPos3d(0.0, ymax, 0.0);
	glutBitmapCharacter(font, 'Y');
	glRasterPos3d(0.0, 0.0, zmax);
	glutBitmapCharacter(font, 'Z');
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	drawAxis();

	glEnable(GL_LIGHTING);
	glutSolidTeapot(0.5);

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

	glutCreateWindow("Lab Camera");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutConfig();
	glutMainLoop();
}
