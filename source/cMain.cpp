/*
TC3022. Computer Graphics
Itzel Reyes P�rez
Jos� Manuel Ballesteros
External geometry loader activity.
*/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif
#include <math.h>
#include <stdio.h>
#include "glm.h"
#include "cCaja.h"
#include "cEscenario.h"
#include "cForklift.h"


#define DO_ROTATION_X
#define  RADDEG  57.29577951f

char		bufferFPS[11];

float XUP[3] = { 1,0,0 }, XUN[3] = { -1, 0, 0 },
YUP[3] = { 0,1,0 }, YUN[3] = { 0,-1, 0 },
ZUP[3] = { 0,0,1 }, ZUN[3] = { 0, 0,-1 },
ORG[3] = { 0,0,0 };

GLfloat viewangle = 0, tippangle = 0, traj[120][3];
GLfloat d[3] = { 0.1, 0.1, 0.1 };

GLfloat		rotationY = 0.0f;
GLfloat		rotationX = 0.0f;

GLfloat*	mat0_specular;
GLfloat*	mat0_diffuse;
GLfloat*	mat0_shininess;
GLfloat*	light0_position;
GLfloat*	light1_position;

cCaja* caja1;
cCaja* caja2;
cCaja* caja3;
cEscenario* escenario;
cForklift* montaCarga;
GLfloat deltaX, deltaY;

void displayText(int x, int y, char* txt);

void mouse(int button, int state, int x, int y)
{

}

void move(int x, int y)
{
	static int lastX = 0, lastY = 0;
	deltaX += lastX - x;
	deltaY += lastY - y;
	lastX = x;
	lastY = y;
}

void moverFL(unsigned char key, int x, int y)
{
	switch (key) {

	case 'w': montaCarga->move(-.05);  break;
	case 's': montaCarga->move(.05);  break;
	case 'a': montaCarga->rotate(2.1);  break;
	case 'd': montaCarga->rotate(-2.1);  break;
	case 'm': montaCarga->lift(0.01);  break;
	case 'n': montaCarga->put(0.01);  break;

	default: printf("   Keyboard %c == %d\n", key, key);
	}

	glutPostRedisplay();
}

void init(void)
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearColor(0.2, 0.2, 0.2, 1.0);

	caja1 = new cCaja();
	caja2 = new cCaja();
	caja3 = new cCaja();
	escenario = new cEscenario();
	montaCarga = new cForklift();

	light0_position = new GLfloat[4];
	light0_position[0] = 0;
	light0_position[1] = 0;
	light0_position[2] = 3;
	light0_position[3] = 1; // POINT LIGHT

	light1_position = new GLfloat[4];
	light1_position[0] = 3;
	light1_position[1] = 0;
	light1_position[2] = 0;
	light1_position[3] = 1; // POINT LIGHT

	mat0_specular = new GLfloat[4];
	mat0_specular[0] = 1.0f;
	mat0_specular[1] = 1.0f;
	mat0_specular[2] = 1.0f;
	mat0_specular[3] = 1.0f;

	mat0_diffuse = new GLfloat[4];
	mat0_diffuse[0] = 0.8f;
	mat0_diffuse[1] = 0.7f;
	mat0_diffuse[2] = 0.6f;
	mat0_diffuse[3] = 1.0f;

	mat0_shininess = new GLfloat[1];
	mat0_shininess[0] = 100.0f;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat0_shininess);
	*/
	glRotatef(deltaX, 0.0, 0.1, 0.0);
	deltaX = 0;

	glPushMatrix();
	{
		glPushMatrix();
		{
			montaCarga->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			escenario->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			caja1->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(0.0, 0.0, 1.0);
			caja2->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(0.0, 0.0, -1.0);
			caja3->draw();
		}
		glPopMatrix();
	}
	glPopMatrix();

	glutSwapBuffers();
}

void idle(void)
{
	rotationY += 0.08f;
	if (rotationY > 360)
	{
		rotationY = 0;
	}

#ifdef DO_ROTATION_X
	rotationX += 0.02f;
	if (rotationX > 360)
	{
		rotationX = 0;
	}
#endif
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)w / (GLdouble)h, 0.01, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2.1, 5.3, 0, 0, 0, 0, 1, 0);
}

void displayText(int x, int y, char* txt)
{
	GLboolean lighting;
	GLint viewportCoords[4];
	glColor3f(0.0, 1.0, 0.0);
	glGetBooleanv(GL_LIGHTING, &lighting);
	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	if (lighting)
	{
		glDisable(GL_LIGHTING);
	}
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, viewportCoords[2], 0.0, viewportCoords[3]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, viewportCoords[3] - y);
	while (*txt)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *txt);
		txt++;
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (lighting)
	{
		glEnable(GL_LIGHTING);
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("OBJ Loader!");
	glutReshapeFunc(reshape);
	glutMotionFunc(move);
	glutMouseFunc(mouse);
	glutKeyboardFunc(moverFL);
	init();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;   /* ANSI C requires main to return int. */
}