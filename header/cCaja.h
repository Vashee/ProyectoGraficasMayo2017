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

class cCaja
{
public:
	cCaja();
	~cCaja();
	void draw();
	GLMmodel* caja;
};

