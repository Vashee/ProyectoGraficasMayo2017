#include "cCaja.h"



cCaja::cCaja()
{
	caja = glmReadOBJ("assets/cube_material.obj");
	glmUnitize(caja);
	glmScale(caja, 0.3f);
	glmFacetNormals(caja);
	glmVertexNormals(caja, 45.0f);
	mass = 0.3f;
	radius = mass;

	pos[0] = 2.0;
	pos[1] = -0.34;
	pos[2] = 0.3;

	oldPos[0] = pos[0];
	oldPos[1] = pos[1];
	oldPos[2] = pos[2];

	forces[0] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;
	forces[1] = 0.0;
	forces[2] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;
}

cCaja::~cCaja()
{
}

void cCaja::draw()
{
	glPushMatrix();
	{
		glTranslated(pos[0], pos[1], pos[2]);
		glmDraw(caja, GLM_SMOOTH | GLM_TEXTURE);
	}
	glPopMatrix();
}

void cCaja::stepSimulation(float dt)
{
	integrateVerlet(dt);
}

void cCaja::clearForces()
{
	forces[0] = 0;
	forces[1] = 0;
	forces[2] = 0;

	dragForce[0] = 0;
	dragForce[1] = 0;
	dragForce[2] = 0;
}

void cCaja::integrateVerlet(float dt)
{
	float accel[3], posAux[3];

	forces[0] -= dragForce[0];
	forces[1] -= dragForce[1];
	forces[2] -= dragForce[2];

	accel[0] = forces[0] / mass;
	accel[1] = forces[1] / mass;
	accel[2] = forces[2] / mass;

	posAux[0] = pos[0];
	posAux[1] = pos[1];
	posAux[2] = pos[2];

	pos[0] = 2.0f * pos[0] - oldPos[0];
	pos[1] = 2.0f * pos[1] - oldPos[1];
	pos[2] = 2.0f * pos[2] - oldPos[2];

	oldPos[0] = posAux[0];
	oldPos[1] = posAux[1];
	oldPos[2] = posAux[2];
}

void cCaja::checkFloorCollisions()
{
	if (pos[1] < radius) {

		pos[1] = radius;
		forces[1] = -restitutionCoefficient * forces[1];

		float dirX = pos[0] - oldPos[0];
		float dirZ = pos[2] - oldPos[2];

		float dX2 = dirX * dirX;
		float dZ2 = dirZ * dirZ;
		float mag = sqrt(dX2 + dZ2);

		dirX /= mag;
		dirZ /= mag;

		dragForce[0] = dirX;
		dragForce[1] = forces[1];
		dragForce[2] = dirZ;
		unitVector(dragForce);
	}
}

bool cCaja::inCollision(cForklift* other)
{
	float x1 = pos[0];
	float x2 = other->px;
	float y1 = pos[1];
	float y2 = other->upDown;
	float z1 = pos[2];
	float z2 = other->pz;

	float deltaX = pow(x1 - x2, 2);
	float deltaY = pow(y1 - y2, 2);
	float deltaZ = pow(z1 - z2, 2);
	float sum = deltaX + deltaY + deltaZ;

	float distBetween = sqrt(sum);
	float r1 = radius;
	float r2 = other->fork->mass;
	float sumR = r1 + r2;

	if (sumR > distBetween) {
		return true;
	}
	else {
		return false;
	}
}