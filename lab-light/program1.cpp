#include <map>

#include <GL/glut.h>

// -------------------------------------------------- //

const double WINDOW_SCALE = 100.0;

// -------------------------------------------------- //

GLdouble camera_angle  = 45.0;
GLdouble camera_radius = 5.0;
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
		BlackPlastic,
		Brass,
		Bronze,
		Chrome,
		Copper,
		Gold,
		Pewter,
		Silver,
		Emerald,
	};
}

// -------------------------------------------------- //

void setLight()
{
	static std::map<Light::Name, Light::Type> lights = {
		{
			Light::Default,
			{
				.ambient  = { 0.2F, 0.2F, 0.2F, 1.0F },
				.diffuse  = { 0.7F, 0.7F, 0.7F, 1.0F },
				.specular = { 1.0F, 1.0F, 1.0F, 1.0F },
				.position = { 2.0F, 1.0F, 2.0F, 0.0F },
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

void setMaterial(Material::Name name = Material::Default)
{
	static std::map<Material::Name, Material::Type> materials = {
		{
			Material::Default,
			{
				.ambient   = { 0.200000F, 0.200000F, 0.200000F, 1.0F },
				.diffuse   = { 1.000000F, 0.000000F, 0.000000F, 1.0F },
				.specular  = { 1.000000F, 1.000000F, 1.000000F, 1.0F },
				.shininess = { 50.0F },
			},
		},
		{
			Material::BlackPlastic,
			{
				.ambient   = { 0.000000F, 0.000000F, 0.000000F, 1.0F },
				.diffuse   = { 0.010000F, 0.010000F, 0.010000F, 1.0F },
				.specular  = { 0.500000F, 0.500000F, 0.500000F, 1.0F },
				.shininess = { 32.0F },
			},
		},
		{
			Material::Brass,
			{
				.ambient   = { 0.329412F, 0.223529F, 0.027451F, 1.0F },
				.diffuse   = { 0.780392F, 0.568627F, 0.113725F, 1.0F },
				.specular  = { 0.992157F, 0.941176F, 0.807843F, 1.0F },
				.shininess = { 27.8974F },
			},
		},
		{
			Material::Bronze,
			{
				.ambient   = { 0.212500F, 0.127500F, 0.027451F, 1.0F },
				.diffuse   = { 0.714000F, 0.428400F, 0.181440F, 1.0F },
				.specular  = { 0.393548F, 0.271906F, 0.166721F, 1.0F },
				.shininess = { 25.6F },
			},
		},
		{
			Material::Chrome,
			{
				.ambient   = { 0.250000F, 0.250000F, 0.250000F, 1.0F },
				.diffuse   = { 0.400000F, 0.400000F, 0.400000F, 1.0F },
				.specular  = { 0.774597F, 0.774597F, 0.774597F, 1.0F },
				.shininess = { 76.8F },
			},
		},
		{
			Material::Copper,
			{
				.ambient   = { 0.191250F, 0.073500F, 0.025000F, 1.0F },
				.diffuse   = { 0.703800F, 0.270480F, 0.082800F, 1.0F },
				.specular  = { 0.256777F, 0.137622F, 0.086014F, 1.0F },
				.shininess = { 12.8F },
			},
		},
		{
			Material::Gold,
			{
				.ambient   = { 0.247250F, 0.199500F, 0.074500F, 1.0F },
				.diffuse   = { 0.751640F, 0.606480F, 0.226480F, 1.0F },
				.specular  = { 0.628281F, 0.555802F, 0.366065F, 1.0F },
				.shininess = { 51.2F },
			},
		},
		{
			Material::Pewter,
			{
				.ambient   = { 0.105880F, 0.058824F, 0.113725F, 1.0F },
				.diffuse   = { 0.427451F, 0.470588F, 0.541176F, 1.0F },
				.specular  = { 0.333300F, 0.333300F, 0.521569F, 1.0F },
				.shininess = { 9.84615F },
			},
		},
		{
			Material::Silver,
			{
				.ambient   = { 0.192250F, 0.192250F, 0.192250F, 1.0F },
				.diffuse   = { 0.507540F, 0.507540F, 0.507540F, 1.0F },
				.specular  = { 0.508273F, 0.508273F, 0.508273F, 1.0F },
				.shininess = { 51.2F },
			},
		},
		{
			Material::Emerald,
			{
				.ambient   = { 0.231250F, 0.231250F, 0.231250F, 1.0F },
				.diffuse   = { 0.277500F, 0.277500F, 0.277500F, 1.0F },
				.specular  = { 0.773911F, 0.773911F, 0.773911F, 1.0F },
				.shininess = { 89.6F },
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
	glutSolidTeapot(1.0);

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

void keyReleased(unsigned char key, __attribute_maybe_unused__ int mouseX, __attribute_maybe_unused__ int mouseY)
{
	switch (key)
	{
	case '1':
		setMaterial(Material::BlackPlastic);
		break;

	case '2':
		setMaterial(Material::Brass);
		break;

	case '3':
		setMaterial(Material::Bronze);
		break;

	case '4':
		setMaterial(Material::Chrome);
		break;

	case '5':
		setMaterial(Material::Copper);
		break;

	case '6':
		setMaterial(Material::Gold);
		break;

	case '7':
		setMaterial(Material::Pewter);
		break;

	case '8':
		setMaterial(Material::Silver);
		break;

	case '9':
		setMaterial(Material::Emerald);
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

	glutKeyboardUpFunc(keyReleased);

	glutConfig();
	glutMainLoop();
}
