#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <map>

#include "./components/linker.hpp"
#include "./components/rail.hpp"
#include "./components/slidebar.hpp"

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_angle  = 45.0;
GLdouble camera_radius = 4.0;
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
		Light0,
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
		Red,
		Black,
		Silver,
		Orange,
	};
}

// -------------------------------------------------- //

GLdouble slider_angle = 0.0;

Rail rail(0.2, 0.2, 0.4, 0.3, 4.0);
SlidebarX slidebarx(0.2, 0.2, 0.4);
SlidebarZ slidebarz(0.2, 0.2, 0.4);
Linker linker(0.2, 0.2, (4.0 - 0.4) / 2);

// -------------------------------------------------- //

void setLight()
{
	static std::map<Light::Name, Light::Type> lights = {
		{
			Light::Light0,
			{
				.ambient  = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.specular = { 1.0F, 1.0F, 1.0F, 1.0F },
				.position = { 10.0F, 10.0F, 10.0F, 0.0F },
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
	glRotated(camera_angle, 0.0, 1.0, 0.0);
}

void setMaterial(Material::Name name)
{
	static std::map<Material::Name, Material::Type> materials = {
		{
			Material::Name::Red,
			{
				.ambient   = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse   = { 1.0F, 0.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.0F },
			},
		},
		{
			Material::Name::Black,
			{
				.ambient   = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse   = { 0.0F, 0.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.0F },
			},
		},
		{
			Material::Name::Silver,
			{
				.ambient   = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse   = { 0.5F, 0.5F, 0.5F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.0F },
			},
		},
		{
			Material::Name::Orange,
			{
				.ambient   = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse   = { 1.0F, 0.5F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.0F },
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
	setCamera();
	setLight();

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

	GLdouble slider_radius = slider_angle * 2 * M_PI / 360.0;

	glDisable(GL_LIGHTING);

	drawAxis();

	glEnable(GL_LIGHTING);

	setMaterial(Material::Red);
	rail.draw_fill();
	setMaterial(Material::Black);
	rail.draw_line();

	glPushMatrix();
	glTranslated((4.0 - 0.4) / 2.0 * cos(slider_radius), 0.0, 0.0);
	setMaterial(Material::Silver);
	slidebarx.draw_fill();
	setMaterial(Material::Black);
	slidebarx.draw_line();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, (4.0 - 0.4) / 2.0 * sin(slider_radius));
	setMaterial(Material::Silver);
	slidebarz.draw_fill();
	setMaterial(Material::Black);
	slidebarz.draw_line();
	glPopMatrix();

	glPushMatrix();
	glTranslated((4.0 - 0.4) / 4.0 * cos(slider_radius), 0.0, (4.0 - 0.4) / 4.0 * sin(slider_radius));
	glRotated(slider_angle, 0.0, 1.0, 0.0);
	setMaterial(Material::Orange);
	linker.draw_fill();
	setMaterial(Material::Black);
	linker.draw_line();
	glPopMatrix();

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
	case 'b':
	case 'B':
		slider_angle += 1.0;
		slider_angle = slider_angle >= 360.0 ? 0.0 : slider_angle;
		break;

	case 'f':
	case 'F':
		slider_angle -= 1.0;
		slider_angle = slider_angle < 0.0 ? 359.0 : slider_angle;
		break;

	default:
		return;
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
		camera_angle = camera_angle - 1.0 < 0 ? 360 : camera_angle - 1.0;
		break;

	case GLUT_KEY_RIGHT:
		camera_angle = camera_angle + 1.0 >= 360 ? 0 : camera_angle + 1.0;
		break;

	default:
		return;
	}

	setCamera();
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

	glutCreateWindow("Lab 3");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialKeyPressed);

	std::cout << "Use <UP> <DOWN> <LEFT> <RIGHT> keys to control the camera" << std::endl;
	std::cout << "Use <F> or <B> keys to move the slider forward (clockwise) or backward (counterclockwise)" << std::endl;

	glutConfig();
	glutMainLoop();
}
