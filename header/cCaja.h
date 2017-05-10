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

class cCaja
{
public:
	cCaja();
	~cCaja();
	void draw();
	GLMmodel* caja;
};

