#pragma once
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#else
#include "freeglut.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#endif

#include "glm.h" 
#include "vecs.h"
#include "cForklift.h"

class cCaja
{
public:
	cCaja();
	~cCaja();
	void draw();
	GLMmodel* caja;
	float pos[3];
	void checkFloorCollisions();
	void stepSimulation(float dt);
	void addForce(float *force);
	bool inCollision(cForklift* other);

private:
	void clearForces();
	void integrateVerlet(float dt);

	float mass;

	float oldPos[3];
	float forces[3];
	float origForces[3];
	float dragForce[3];

	float radius;
	float restitutionCoefficient;
};

