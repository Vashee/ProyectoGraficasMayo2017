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

#include "cFork.h"


class cForklift
{
public:
	cForklift();
	~cForklift();
	void update();
	void draw();
	void move(float fwdBack);
	void rotate(float rotar);
	void lift(float levantar);
	void put(float bajar);
	GLMmodel* forkLift;
	cFork* fork;
};

