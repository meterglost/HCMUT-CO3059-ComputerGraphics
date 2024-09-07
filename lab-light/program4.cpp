#include <iostream>
#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_radius = 5.0;
GLdouble camera_height = 5.0;

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
		Red,
		Green,
		Blue,
		Yellow,
		Orange,
		Purple,
	};
}

// -------------------------------------------------- //

void setLight()
{
	static std::map<Light::Name, Light::Type> lights = {
		{
			Light::Default,
			{
				.ambient  = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.specular = { 1.0F, 1.0F, 1.0F, 1.0F },
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

void setMaterial(Material::Name name)
{
	static std::map<Material::Name, Material::Type> materials = {
		{
			Material::Red,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 1.0F, 0.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
		{
			Material::Green,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 0.0F, 1.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
		{
			Material::Blue,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 0.0F, 0.0F, 1.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
		{
			Material::Yellow,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 1.0F, 1.0F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
		{
			Material::Orange,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 1.0F, 0.5F, 0.0F, 1.0F },
				.specular  = { 1.0F, 1.0F, 1.0F, 1.0F },
				.shininess = { 100.8F },
			},
		},
		{
			Material::Purple,
			{
				.ambient   = { 0.1F, 0.1F, 0.1F, 1.0F },
				.diffuse   = { 1.0F, 0.0F, 1.0F, 1.0F },
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

	glClearColor(0.8F, 0.8F, 0.8F, 1.0F);

	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLUquadricObj *obj;
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);

	// draw the head
	glPushMatrix();
	glTranslated(0.0, 1.2, 0.0);
	setMaterial(Material::Yellow);
	glutSolidSphere(0.7, 50, 50);
	glPopMatrix();

	// draw the chest
	glPushMatrix();
	setMaterial(Material::Green);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	// draw the abdomen
	glPushMatrix();
	glTranslated(0.0, -1.8, 0.0);
	setMaterial(Material::Red);
	glutSolidSphere(1.3, 50, 50);
	glPopMatrix();

	// draw nose
	glPushMatrix();
	glTranslated(0.0, 1.2, 0.7);
	setMaterial(Material::Red);
	glutSolidSphere(0.2, 50, 50);
	glPopMatrix();

	// draw left eye
	glPushMatrix();
	glTranslated(-0.3, 1.3, 0.6);
	setMaterial(Material::Green);
	glutSolidSphere(0.1, 50, 50);
	glPopMatrix();

	// draw right eye
	glPushMatrix();
	glTranslated(+0.3, 1.3, 0.6);
	setMaterial(Material::Green);
	glutSolidSphere(0.1, 50, 50);
	glPopMatrix();

	// draw the hat
	glPushMatrix();
	glTranslated(0.0, 1.6, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	setMaterial(Material::Red);
	glutSolidCone(0.65, 1.2, 20, 30);
	glPopMatrix();

	// draw left hand
	glPushMatrix();
	glTranslated(0.0, 0.4, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	setMaterial(Material::Purple);
	gluCylinder(obj, 0.4, 0.4, 3.0, 30, 10);
	glPopMatrix();

	// draw right hand
	glPushMatrix();
	glTranslated(0.0, 0.4, 0.0);
	glRotated(+90.0, 0.0, 1.0, 0.0);
	setMaterial(Material::Purple);
	gluCylinder(obj, 0.4, 0.4, 3.0, 30, 10);
	glPopMatrix();

	// draw noel tree
	glPushMatrix();
	glTranslated(0.0, +1.0, 5.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	setMaterial(Material::Green);
	glutSolidCone(0.8, 2.5, 30, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -1.0, 5.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	setMaterial(Material::Green);
	glutSolidCone(0.8, 2.5, 30, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, -3.0, 5.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
	setMaterial(Material::Orange);
	gluCylinder(obj, 0.4, 0.4, 3, 30, 10);
	glPopMatrix();

	gluDeleteQuadric(obj);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	const double VIRTUAL_WIDTH  = width / WINDOW_SCALE;
	const double VIRTUAL_HEIGHT = height / WINDOW_SCALE;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60.0, VIRTUAL_WIDTH / VIRTUAL_HEIGHT, 0.5, 100.0);

	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void rotate(int value)
{
	glMatrixMode(GL_MODELVIEW);
	glRotated(2.0, 0.0, 1.0, 0.0);

	glutPostRedisplay();
	glutTimerFunc(50, rotate, value);
}

void keyPressed(unsigned char key, __attribute_maybe_unused__ int mouseX, __attribute_maybe_unused__ int mouseY)
{
	switch (key)
	{
	case 'o':
		glIsEnabled(GL_LIGHTING) ? glDisable(GL_LIGHTING) : glEnable(GL_LIGHTING);
		break;

	case 's':
		GLdouble shadeModel;
		glGetDoublev(GL_SHADE_MODEL, &shadeModel);
		glShadeModel(shadeModel == GL_SMOOTH ? GL_FLAT : GL_SMOOTH);
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

	glutCreateWindow("Lab Light");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glutTimerFunc(50, rotate, 0);
	glutKeyboardFunc(keyPressed);

	std::cout << "<o>. Turn on/off the light" << std::endl;
	std::cout << "<s>. Turn on/off smooth shading" << std::endl;

	glutConfig();
	glutMainLoop();
}
