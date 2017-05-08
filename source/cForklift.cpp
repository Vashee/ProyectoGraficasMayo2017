#include "cForklift.h"

float yAngle, zeto, px, pz, rot;
float py = 0.035f;
float upDown = -0.6f;

cForklift::cForklift()
{
	forkLift = glmReadOBJ("assets/ForkLift/ForkLift.obj");
	glmUnitize(forkLift);
	glmFacetNormals(forkLift);
	glmVertexNormals(forkLift, 45.0f);
	fork = new cFork();
}


cForklift::~cForklift()
{

}

void cForklift::update()
{

}

void cForklift::draw() {
	glPushMatrix();
	{
		glTranslatef(px, py, pz); 
		glRotatef(rot-90, 0, 1, 0);
		glmDraw(forkLift, GLM_SMOOTH | GLM_TEXTURE);
		glTranslatef(-0.3, upDown, 0.72);
		fork->draw();
	}
	glPopMatrix();
}

void cForklift::move(float fwdBack) {
	px = px + fwdBack * cos(0.0174533f * rot);
	py = 0.035f;
	pz = pz - fwdBack * sin(0.0174533f * rot);
}

void cForklift::rotate(float rotar) {
	rot = rot + rotar;
}

void cForklift::lift(float levantar) {
	if (upDown <= -0.1) {
		upDown = upDown + levantar;
	}
}

void cForklift::put(float bajar) {
	if (upDown >= -0.6) {
		upDown = upDown - bajar;
	}
}
