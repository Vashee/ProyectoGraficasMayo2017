/*
TC3022. Computer Graphics
Itzel Reyes Pérez
José Manuel Ballesteros
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

int counter = 0;
cCaja* cajas[6];
cEscenario* escenario;
cForklift* montaCarga;
GLfloat deltaX, deltaY;

long frames, time_, timebase = 0;
unsigned long frameCount;
float fps = 0.0;
char bufferFPS[11];
void displayText(int x, int y, char *txt);

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
	case 'n': 
		for (int i = 0; i < 6; i++) {
			if (cajas[i]->visible == false) {
				cajas[i]->x = montaCarga->px - 1 * cos(0.0174533f * montaCarga->rotM);
				cajas[i]->y = 0;
				cajas[i]->z = montaCarga->pz + 1 * sin(0.0174533f * montaCarga->rotM);
				cajas[i]->visible = true;
				montaCarga->switchModel();
				if (cajas[i]->count == false) {
					counter += 1;
					cajas[i]->count = true;
					montaCarga->cajaIs = false;
				}
				break;
			}
		}

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

	int count = 0;
	for (int row = 0; row < 1; row++) {
		for (int col = 0; col < 6; col++) {
			float row2 = row;
			if (row2 > 0) {
				row2 = 0.7f;
			}
			cajas[count++] = new cCaja(2, row2, col - 3);
		}
	}
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

void collisions()
{
	for (int y = 0; y < 6; y++) {
		bool crash = false;
		if (cajas[y]->inCollision(montaCarga) && montaCarga->cajaIs == false) {
			cajas[y]->visible = false;
			cajas[y]->x = montaCarga->px - 1.5 * cos(0.0174533f * montaCarga->rotM);
			cajas[y]->y = 0;
			cajas[y]->z = montaCarga->pz + 1.5 * sin(0.0174533f * montaCarga->rotM);
			montaCarga->switchModel();
			montaCarga->cajaIs = true;
			break;
		}
	}
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
		for (int i = 0; i < 6; i++) {
			cajas[i]->draw();
		}
	}
	glPopMatrix();
	displayText(5, 20, bufferFPS);
	glutSwapBuffers();
}

void idle(void)
{
	frames++;
	time_ = glutGet(GLUT_ELAPSED_TIME);
	if (time_ - timebase > 1000) {
		fps = frames*1000.0f / (time_ - timebase);
		sprintf(bufferFPS, "FPS:%4.2f\n, Score:%d", time_ / 1000.0f, counter);
		timebase = time_;
		frames = 0;
	}

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
	collisions();
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
	srand(time(NULL));
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
