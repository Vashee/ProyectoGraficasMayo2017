#include "cEscenario.h"

cEscenario::cEscenario()
{
	piso = glmReadOBJ("assets/plane.obj");
	glmUnitize(piso);
	glmScale(piso, 8.0f);
	glmFacetNormals(piso);
	glmVertexNormals(piso, 45.0f);


	cajas = new cCaja*[NUM_CAJAS];

	for (int c = 0; c < NUM_CAJAS; c++) {
		cajas[c] = new cCaja();
	}
}


cEscenario::~cEscenario()
{
}


void cEscenario::draw()
{
	glPushMatrix();
	{
		glPushMatrix();
		{
			glTranslated(0.0, -0.6, 0.0);
			glmDraw(piso, GLM_SMOOTH | GLM_TEXTURE);
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(-4.0, 0.0, 0.0);
			cajas[0]->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(-4.0, 0.0, 0.7);
			cajas[1]->draw();
		}
		glPopMatrix();
		{
			glTranslated(-4.0, 0.0, 1.4);
			cajas[2]->draw();
		}
		glPopMatrix();
		{
			glTranslated(-4.0, 0.0, -0.7);
			cajas[3]->draw();
		}
		glPopMatrix();
		{
			glTranslated(-4.0, 0.0, -1.4);
			cajas[4]->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(-4.0, 0.63, 0.0);
			cajas[5]->draw();
		}
		glPopMatrix();
		glPushMatrix();
		{
			glTranslated(-4.0, 00.63, 0.7);
			cajas[6]->draw();
		}
		glPopMatrix();
	}
	glPopMatrix();

}
