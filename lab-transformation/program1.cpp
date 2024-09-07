#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 50.0;

// -------------------------------------------------- //

void glutConfig()
{
	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void drawGrid()
{
	const int WINDOW_WIDTH  = glutGet(GLUT_WINDOW_WIDTH);
	const int WINDOW_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);

	const double VIRTUAL_WIDTH  = WINDOW_WIDTH / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = WINDOW_HEIGHT / WINDOW_SCALE;

	glLineWidth(1.0F);

	glColor3d(0.6, 0.6, 0.6);
	glBegin(GL_LINES);

	for (GLdouble x = 0.0; x < VIRTUAL_WIDTH / 2; x += 1.0)
	{
		glVertex2d(+x, +VIRTUAL_HEIGHT / 2);
		glVertex2d(+x, -VIRTUAL_HEIGHT / 2);
		glVertex2d(-x, +VIRTUAL_HEIGHT / 2);
		glVertex2d(-x, -VIRTUAL_HEIGHT / 2);
	}

	for (GLdouble y = 0.0; y < VIRTUAL_HEIGHT / 2; y += 1.0)
	{
		glVertex2d(+VIRTUAL_WIDTH / 2, +y);
		glVertex2d(-VIRTUAL_WIDTH / 2, +y);
		glVertex2d(+VIRTUAL_WIDTH / 2, -y);
		glVertex2d(-VIRTUAL_WIDTH / 2, -y);
	}

	glEnd();

	glLineWidth(2.0F);

	glColor3d(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2d(0.0, +VIRTUAL_HEIGHT / 2);
	glVertex2d(0.0, -VIRTUAL_HEIGHT / 2);
	glVertex2d(+VIRTUAL_WIDTH / 2, 0.0);
	glVertex2d(-VIRTUAL_WIDTH / 2, 0.0);
	glEnd();
}

void drawHouse()
{
	glLineWidth(2.0F);

	glBegin(GL_LINE_LOOP);
	glVertex2d(0.0, 0.0);
	glVertex2d(0.0, 2.0);
	glVertex2d(1.5, 3.5);
	glVertex2d(1.5, 4.0);
	glVertex2d(0.5, 4.0);
	glVertex2d(0.5, 2.5);
	glVertex2d(2.0, 4.0);
	glVertex2d(4.0, 2.0);
	glVertex2d(4.0, 0.0);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	drawGrid();

	glPushMatrix();
	glColor3d(1.0, 0.0, 0.0);
	drawHouse();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4.0, 3.0, 0.0);
	glColor3d(0.0, 0.0, 1.0);
	drawHouse();
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.0, -3.0, 0.0);
	glScaled(1.0, 1.5, 0.0);
	glColor3d(1.0, 0.0, 1.0);
	drawHouse();
	glPopMatrix();

	glPushMatrix();
	glRotated(90.0, 0.0, 0.0, 1.0);
	glTranslated(2.0, 0.0, 0.0);
	glColor3d(0.0, 1.0, 1.0);
	drawHouse();
	glPopMatrix();

	glPushMatrix();
	glScaled(1.5, 1.5, 0.0);
	glRotated(180.0, 0.0, 0.0, 1.0);
	glColor3d(0.0, 0.0, 0.0);
	drawHouse();
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
	gluOrtho2D(-VIRTUAL_WIDTH / 2, +VIRTUAL_WIDTH / 2, -VIRTUAL_HEIGHT / 2, +VIRTUAL_HEIGHT / 2);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

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

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((SCREEN_WIDTH - WINDOW_WIDTH) / 2, (SCREEN_HEIGHT - WINDOW_HEIGHT) / 2);

	glutCreateWindow("Lab Transformation");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutConfig();
	glutMainLoop();
}
