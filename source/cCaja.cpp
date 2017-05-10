#include "cCaja.h"



cCaja::cCaja(float x1, float y1, float z1)
{
	caja = glmReadOBJ("assets/cube_material.obj");
	glmUnitize(caja);
	glmScale(caja, 0.3f);
	glmFacetNormals(caja);
	glmVertexNormals(caja, 45.0f);
	mass = 0.55f;
	radius = mass;
	visible=true;

	x = x1;
	y = y1;
	z = z1;

	oldPos[0] = x;
	oldPos[1] = y;
	oldPos[2] = z;

	forces[0] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;
	forces[1] = 0.0;
	forces[2] = -10 + 20.0f * ((float)rand()) / (float)RAND_MAX;
}

cCaja::~cCaja()
{
}

void cCaja::draw()
{
	if (visible) {
		glPushMatrix();
		{
			glTranslated(x, y, z);
			glmDraw(caja, GLM_SMOOTH | GLM_TEXTURE);
		}
		glPopMatrix();
	}
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

	posAux[0] = x;
	posAux[1] = y;
	posAux[2] = z;

	x = 2.0f * x - oldPos[0];
	y = 2.0f * y - oldPos[1];
	z = 2.0f * z - oldPos[2];

	oldPos[0] = posAux[0];
	oldPos[1] = posAux[1];
	oldPos[2] = posAux[2];
}

void cCaja::checkFloorCollisions()
{
	if (y < radius) {

		y = radius;
		forces[1] = -restitutionCoefficient * forces[1];

		float dirX = x - oldPos[0];
		float dirZ = z - oldPos[2];

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
	float x1 = x;
	float x2 = other->px;
	float y1 = y;
	float y2 = other->upDown;
	float z1 = z;
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
