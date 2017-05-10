#include "cFork.h"



cFork::cFork()
{
	forkIzq = glmReadOBJ("assets/cube.obj");
	glmUnitize(forkIzq);
	forkDer = glmReadOBJ("assets/cube.obj");
	glmUnitize(forkDer);
	glmFacetNormals(forkIzq);
	glmFacetNormals(forkDer);
	glmVertexNormals(forkIzq, 45.0f);
	glmVertexNormals(forkDer, 45.0f);
	mass = 0.1f;
}


cFork::~cFork()
{
}

void cFork::draw()
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			glTranslated(0.5, 0.0, 0.0);
			//glmDraw(caja, GLM_SMOOTH | GLM_TEXTURE);
			glScaled(0.05, 0.01, 0.27);
			glmDraw(forkIzq, GLM_SMOOTH);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(0.1, 0.0, 0.0);
			//glmDraw(caja, GLM_SMOOTH | GLM_TEXTURE);
			glScaled(0.05, 0.01, 0.27);
			glmDraw(forkDer, GLM_SMOOTH);
		}
		glPopMatrix();
	}
	glPopMatrix();
}
