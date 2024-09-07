#include <stdio.h>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_radius = 2.0;
GLdouble camera_height = 1.5;

// -------------------------------------------------- //

void setCamera()
{
	glLoadIdentity();
	gluLookAt(camera_radius, camera_height, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void glutConfig()
{
	setCamera();

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	static const GLdouble vertices[][3] = {
		{ -1.0, -1.0, -1.0 },
		{ -1.0, +1.0, -1.0 },
		{ +1.0, +1.0, -1.0 },
		{ +1.0, -1.0, -1.0 },
		{ -1.0, -1.0, +1.0 },
		{ -1.0, +1.0, +1.0 },
		{ +1.0, +1.0, +1.0 },
		{ +1.0, -1.0, +1.0 },
	};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS); // Front
	glColor3d(1.0, 0.5, 0.5);
	glVertex3dv(vertices[0]);
	glVertex3dv(vertices[1]);
	glVertex3dv(vertices[2]);
	glVertex3dv(vertices[3]);
	glEnd();

	glBegin(GL_QUADS); // Back
	glColor3d(1.0, 0.5, 0.5);
	glVertex3dv(vertices[4]);
	glVertex3dv(vertices[5]);
	glVertex3dv(vertices[6]);
	glVertex3dv(vertices[7]);
	glEnd();

	glBegin(GL_QUADS); // Ledt
	glColor3d(0.5, 1.0, 0.5);
	glVertex3dv(vertices[0]);
	glVertex3dv(vertices[1]);
	glVertex3dv(vertices[5]);
	glVertex3dv(vertices[4]);
	glEnd();

	glBegin(GL_QUADS); // Right
	glColor3d(0.5, 1.0, 0.5);
	glVertex3dv(vertices[2]);
	glVertex3dv(vertices[3]);
	glVertex3dv(vertices[7]);
	glVertex3dv(vertices[6]);
	glEnd();

	glBegin(GL_QUADS); // Top
	glColor3d(0.5, 0.5, 1.0);
	glVertex3dv(vertices[1]);
	glVertex3dv(vertices[2]);
	glVertex3dv(vertices[6]);
	glVertex3dv(vertices[5]);
	glEnd();

	glBegin(GL_QUADS); // Bottom
	glColor3d(0.5, 0.5, 1.0);
	glVertex3dv(vertices[0]);
	glVertex3dv(vertices[3]);
	glVertex3dv(vertices[7]);
	glVertex3dv(vertices[4]);
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
	glOrtho(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void rotate(int value)
{
	glRotated(2.0, 0.0, 1.0, 0.0);

	glutPostRedisplay();
	glutTimerFunc(50, rotate, value);
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
		printf("Screen size is too small to run this program\n");
		return 1;
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	glutCreateWindow("Lab 1 - Dynamic cube");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(50, rotate, 0);

	glutConfig();
	glutMainLoop();
}
