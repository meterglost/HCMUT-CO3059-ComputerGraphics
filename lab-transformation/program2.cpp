#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 200.0;

// -------------------------------------------------- //

size_t drawState = 0;

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
		Default,
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
			Light::Default,
			{
				.diffuse  = { 0.7F, 0.7F, 0.7F, 1.0F },
				.position = { 5.0F, 5.0F, 5.0F, 0.0F },
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
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
	GLdouble xmin = -1.5, xmax = 1.5;
	GLdouble ymin = -1.5, ymax = 1.5;
	GLdouble zmin = -1.5, zmax = 1.5;

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

	switch (drawState)
	{
	case 1:
		glPushMatrix();
		glTranslated(1.0, 0.0, 0.0);
		glutSolidTeapot(0.25);
		glPopMatrix();
		break;

	case 2:
		glPushMatrix();

		glBegin(GL_LINE_LOOP);
		glVertex3d(0.5, 0.0, 0.0);
		glVertex3d(0.5, 1.0, 0.0);
		glVertex3d(0.5, 1.0, 0.9);
		glVertex3d(0.5, 0.0, 0.9);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3d(0.0, 0.0, 0.9);
		glVertex3d(0.0, 1.0, 0.9);
		glVertex3d(0.5, 1.0, 0.9);
		glVertex3d(0.5, 0.0, 0.9);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3d(0.0, 1.0, 0.0);
		glVertex3d(0.5, 1.0, 0.0);
		glVertex3d(0.5, 1.0, 0.9);
		glVertex3d(0.0, 1.0, 0.9);
		glEnd();

		glTranslated(0.5, 1.0, 0.9);
		glutSolidTeapot(0.25);

		glPopMatrix();

		break;

	case 3:
		glPushMatrix();
		glTranslated(0.0, 0.0, 1.0);
		glRotated(90.0, 0.0, 1.0, 0.0);
		glutSolidTeapot(0.25);
		glPopMatrix();
		break;

	case 4:
		glPushMatrix();
		glRotatef(60.0, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 1.0, 0.0);
		glScalef(0.5, 0.5, 0.5);
		glutSolidTeapot(0.25);
		glPopMatrix();
		break;

	case 5:
		for (GLdouble angle = 0.0; angle < 360.0; angle += 90.0)
		{
			glPushMatrix();
			glRotated(angle, 0.0, 1.0, 0.0);
			glTranslated(1.0, 0.0, 0.0);
			glutSolidTeapot(0.25);
			glPopMatrix();
		}
		break;

	case 6:
		for (size_t i = 0; i < 5; ++i)
		{
			glPushMatrix();
			glTranslated(0.0, 0.3 * (GLdouble)i, 0.0);
			for (size_t j = 0; j < i; ++j)
				glScaled(0.8, 0.8, 0.8);
			glutSolidTeapot(0.25);
			glPopMatrix();
		}
		break;

	case 7:
		for (size_t i = 0; i < 5; ++i)
		{
			for (size_t j = 0; j < 5 - i; ++j)
			{
				glPushMatrix();
				glTranslated(0.3 * (GLdouble)i, 0.3 * (GLdouble)j, 0.0);
				glutSolidCube(0.2);
				glPopMatrix();

				glPushMatrix();
				glTranslated(0.3 * (GLdouble)i, 0.0, 0.3 * (GLdouble)j);
				glutSolidCube(0.2);
				glPopMatrix();
			}
		}
		break;

	case 8:
		glPushMatrix();
		for (size_t i = 0; i < 5; ++i)
		{
			glutSolidCube(0.3);
			glRotated(45.0, 1.0, 0.0, 0.0);
			glTranslated(0.3, 0.0, 0.0);
			glScaled(0.8, 0.8, 0.8);
		}
		glPopMatrix();

		glPushMatrix();
		for (size_t i = 0; i < 5; ++i)
		{
			glutSolidCube(0.3);
			glRotated(45.0, 0.0, 1.0, 0.0);
			glTranslated(0.0, 0.3, 0.0);
			glScaled(0.8, 0.8, 0.8);
		}
		glPopMatrix();

		glPushMatrix();
		for (size_t i = 0; i < 5; ++i)
		{
			glutSolidCube(0.3);
			glRotated(45.0, 0.0, 0.0, 1.0);
			glTranslated(0.0, 0.0, 0.3);
			glScaled(0.8, 0.8, 0.8);
		}
		glPopMatrix();

		break;

	default:
		break;
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
	if ('1' <= key && key <= '8')
		drawState = key - '0';
	else
		return;

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

	glutCreateWindow("Lab Transformation");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(keyPressed);

	glutConfig();
	glutMainLoop();
}
