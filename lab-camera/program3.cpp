#include <iostream>
#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_angle  = 0.0;
GLdouble camera_height = 2.0;
GLdouble camera_radius = 5.0;

// -------------------------------------------------- //

bool single_view = true;

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
	setMaterial();

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void setMatrix1(const double VIRTUAL_WIDTH, const double VIRTUAL_HEIGHT)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void setMatrix2(const double VIRTUAL_WIDTH, const double VIRTUAL_HEIGHT)
{
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, VIRTUAL_WIDTH / VIRTUAL_HEIGHT, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void display()
{
	const int WINDOW_WIDTH  = glutGet(GLUT_WINDOW_WIDTH);
	const int WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

	const double VIRTUAL_WIDTH  = WINDOW_WIDTH / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = WINDOW_HEIGHT / WINDOW_SCALE;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.0F, 0.0F, 1.0F);

	if (!single_view)
	{
		setMatrix1(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

		glPushMatrix();
		glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		gluLookAt(0.0, camera_height, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
		glRotated(camera_angle, 0.0, 1.0, 0.0);
		glutSolidTeapot(1);
		glPopMatrix();

		glPushMatrix();
		glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		gluLookAt(camera_radius, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glRotated(camera_angle, 0.0, 1.0, 0.0);
		glutSolidTeapot(1);
		glPopMatrix();

		glPushMatrix();
		glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		gluLookAt(0.0, 0.0, camera_radius, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glRotated(camera_angle, 0.0, 1.0, 0.0);
		glutSolidTeapot(1);
		glPopMatrix();

		setMatrix2(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

		glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		gluLookAt(camera_radius, camera_height, camera_radius, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glRotated(camera_angle, 0.0, 1.0, 0.0);
		glutSolidTeapot(1);
	}
	else
	{
		setMatrix2(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);

		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		gluLookAt(camera_radius, camera_height, camera_radius, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glRotated(camera_angle, 0.0, 1.0, 0.0);

		glutSolidTeapot(1);
	}

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

void keyPressed(unsigned char key, __attribute_maybe_unused__ int mouseX, __attribute_maybe_unused__ int mouseY)
{
	switch (key)
	{
	case '\t':
		single_view = !single_view;
		break;
	case '+':
		camera_radius -= 0.1;
		break;
	case '-':
		camera_radius += 0.1;
		break;
	}

	glutPostRedisplay();
}

void specialKeyPressed(int key, __attribute_maybe_unused__ int mouseX, __attribute_maybe_unused__ int mouseY)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera_height += 0.1;
		break;
	case GLUT_KEY_DOWN:
		camera_height -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		camera_angle = (camera_angle + 1 >= 360) ? 0 : camera_angle + 1;
		break;
	case GLUT_KEY_RIGHT:
		camera_angle = (camera_angle - 1 < 0) ? 360 : camera_angle - 1;
		break;

	default:
		return;
	}

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

	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);

	std::cout << "Tab: Switch between single and quadruple views." << std::endl
			  << "+/-: increase/decrease camera distance." << std::endl
			  << "up/down    : increase/decrease camera height." << std::endl
			  << "left/right : rotate camera to the left/right" << std::endl;

	glutConfig();
	glutMainLoop();
}
