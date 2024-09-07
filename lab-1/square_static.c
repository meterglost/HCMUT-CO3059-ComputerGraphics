#include <stdio.h>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

void glutConfig()
{
	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 0.5, 0.5);

	glBegin(GL_POLYGON);
	glVertex2d(-1.0, -1.0);
	glVertex2d(-1.0, +1.0);
	glVertex2d(+1.0, +1.0);
	glVertex2d(+1.0, -1.0);
	glEnd();

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	const double VIRTUAL_WIDTH  = width / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = height / WINDOW_SCALE;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2);

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
	{
		printf("Screen size is too small to run this program");
		return 1;
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	glutCreateWindow("Lab 1 - Static square");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutConfig();
	glutMainLoop();
}
