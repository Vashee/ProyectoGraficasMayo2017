#include "cCaja.h"



cCaja::cCaja()
{
	caja = glmReadOBJ("assets/cube_material.obj");
	// When the model is too big make it fit inside a 1x1x1 cube:
	glmUnitize(caja);
	// You can also scale it later:
	glmScale(caja, 0.3f);
	// When the model doesn't have normals, glm can add them automatically for you:
	glmFacetNormals(caja);
	glmVertexNormals(caja, 45.0f);
}


cCaja::~cCaja()
{
}

void cCaja::draw()
{
	glPushMatrix();
	{
		glTranslated(2.0, -0.34, 0.3);
		glmDraw(caja, GLM_SMOOTH | GLM_TEXTURE);
	}
	glPopMatrix();
}