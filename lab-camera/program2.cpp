#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

// GLdouble camera_angle  = 45.0;
GLdouble camera_radius = 1.5;
GLdouble camera_height = 2.0;

// -------------------------------------------------- //

void setCamera()
{
	glLoadIdentity();
	gluLookAt(camera_radius, camera_height, camera_radius, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// glRotated(camera_angle, 0.0, 1.0, 0.0);
}

void glutConfig()
{
	setCamera();

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void drawGrid()
{
	glLineWidth(1.0F);

	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);

	for (GLdouble x = 0.0, dx = 0.2; x < 10.0; x += dx)
	{
		glVertex3d(+x, 0.0, +10.0);
		glVertex3d(+x, 0.0, -10.0);

		glVertex3d(-x, 0.0, +10.0);
		glVertex3d(-x, 0.0, -10.0);
	}

	for (GLdouble z = 0.0, dz = 0.2; z < 10.0; z += dz)
	{
		glVertex3d(+10.0, 0.0, +z);
		glVertex3d(-10.0, 0.0, +z);

		glVertex3d(+10.0, 0.0, -z);
		glVertex3d(-10.0, 0.0, -z);
	}

	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const int WINDOW_WIDTH  = glutGet(GLUT_WINDOW_WIDTH);
	const int WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

	const double VIRTUAL_WIDTH  = WINDOW_WIDTH / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = WINDOW_HEIGHT / WINDOW_SCALE;

	// Viewport 1

	glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	glOrtho(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	drawGrid();

	// Viewport 2

	glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60, VIRTUAL_WIDTH / VIRTUAL_HEIGHT, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	drawGrid();

	//

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
