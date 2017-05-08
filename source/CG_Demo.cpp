/*
* 
*
*Created by José Manuel Ballesteros Lailson A01128723 
*
*/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#endif
#include "cAthom.h"
#include "cParticle1.h"
#include "cParticle2.h"

//ParAtomica* atomo;
cAthom* atomo;

float rotacion;

void init() {

	atomo = new cAthom();
	rotacion = 0.0f;


	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
}

void display() {							// Called for each frame (about 60 times per second).

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0.0, 0.0, 10.0,	// Where the cam is									// Where the camera is.
		0.0, 0.0, 0.0,	// Cam pivot									// To where the camera points at.
		0.0, 1.0, 0.0);

	atomo->draw();


	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle() {															// Called when drawing is finished.

	rotacion = 0.0f;
	glutPostRedisplay();											// Display again.
}

void reshape(int x, int y) {											// Called when the window geometry changes.

	glMatrixMode(GL_PROJECTION);	 // 2D								// Go to 2D mode.
	glLoadIdentity();												// Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);		// Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW); // 3D										// Go to 3D mode.
	glViewport(0, 0, x, y);											// Configure the camera frame dimensions.
	gluLookAt(0.0, 3.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	display();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);

	init();
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.

	glutMainLoop();													// Begin graphics program.
	return 0;
}
