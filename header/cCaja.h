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
#include "vecs.h"
#include "cForklift.h"

class cCaja
{
public:
    cCaja(float _x, float _y, float _z);
    ~cCaja();
    void draw();
    GLMmodel* caja;
    float x;
    float y;
    float z;
    float pos[3];
    void checkFloorCollisions();
    void stepSimulation(float dt);
    void addForce(float *force);
    bool inCollision(cForklift* other);
    bool visible;
    
private:
    void clearForces();
    void integrateVerlet(float dt);
    
    float mass;
    
    float oldPos[3];
    float forces[3];
    float origForces[3];
    float dragForce[3];
    
    float radius;
    float restitutionCoefficient;
};

