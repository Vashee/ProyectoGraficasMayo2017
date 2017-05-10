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

class cFork
{
public:
	cFork();
	~cFork();
	void draw();
	GLMmodel* forkIzq;
	GLMmodel* forkDer;
};

