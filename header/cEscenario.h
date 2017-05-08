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
#include "glm.h"
#endif

#include "cCaja.h"

#define NUM_CAJAS 7
class cEscenario
{
public:
	cEscenario();
	~cEscenario();
	void draw();
	GLMmodel* piso;
	cCaja** cajas;
};

