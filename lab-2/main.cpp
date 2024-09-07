#include <GL/glut.h>

#include "./components/base.hpp"

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_angle  = 45.0;
GLdouble camera_radius = 2.0;
GLdouble camera_height = 1.5;

// -------------------------------------------------- //

extern Object object;

// -------------------------------------------------- //

void setCamera()
{
	glLoadIdentity();
	gluLookAt(camera_radius, camera_height, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotated(camera_angle, 0.0, 1.0, 0.0);
}

void glutConfig()
{
	setCamera();

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
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

	drawAxis();
	object.draw_fill();
	object.draw_line();

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

void keyPressed(int key, __attribute_maybe_unused__ int mouseX, __attribute_maybe_unused__ int mouseY)
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

	glutCreateWindow("Lab 2");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutSpecialFunc(keyPressed);

	glutConfig();
	glutMainLoop();
}
