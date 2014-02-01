#include <iostream>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "camera.h"
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>	//you may need to change this

camera cam;
GLUquadricObj* quad;
btDynamicsWorld* world;
btDispatcher* dispatcher;
btCollisionConfiguration* collisionConfig;
btBroadphaseInterface* broadphase;
btConstraintSolver* solver;
std::vector<btRigidBody*> bodies;

btRigidBody* addSphere(float rad, float x, float y, float z, float mass)
{
	btTransform t;
	t.setOrigin(btVector3(x, y, z));
	t.setIdentity();
	btSphereShape* sphere = new btSphereShape(rad);
	btVector3 inertia(0, 0, 0);
	if(mass != 0)
		sphere->calculateLocalInertia(mass, inertia);

	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motion, sphere, inertia);
	btRigidBody* body = new btRigidBody(info);
	world->addRigidBody(body);
	bodies.push_back(body);

	return body;
}

void renderSphere(btRigidBody* sphere)
{
	if(sphere->getCollisionShape()->getShapeType() != SPHERE_SHAPE_PROXYTYPE)
		return;

	glColor3f(1, 0, 0);
	float r = ((btSphereShape*)sphere->getCollisionShape())->getRadius();
	btTransform t;
	sphere->getMotionState()->getWorldTransform(t);
	float mat[16];
	t.getOpenGLMatrix(mat);
	glPushMatrix();
		glMultMatrixf(mat);
		gluSphere(quad, r, 20, 20);
	glPopMatrix();
}

void renderPlane(btRigidBody* plane)
{
	if(plane->getCollisionShape()->getShapeType() != STATIC_PLANE_PROXYTYPE)
		return;

	glColor3f(.5, .5, .5);
	btTransform t;
	plane->getMotionState()->getWorldTransform(t);
	float mat[16];
	t.getOpenGLMatrix(mat);
	glPushMatrix();
		glMultMatrixf(mat);
		glBegin(GL_QUADS);
			glVertex3f(-1000, 0, 1000);
			glVertex3f(-1000, 0, -1000);
			glVertex3f(1000, 0, -1000);
			glVertex3f(1000, 0, 1000);
		glEnd();
	glPopMatrix();
}

void init(float angle)
{
	collisionConfig = new btDefaultCollisionConfiguration;
	dispatcher = new btCollisionDispatcher(collisionConfig);
	broadphase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
	world->setGravity(btVector3(0, -10, 0));

	btTransform t;
	t.setOrigin(btVector3(0, 0, 0));
	t.setIdentity();
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(t);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);
	world->addRigidBody(body);
	bodies.push_back(body);

	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angle,640.0/480.0,1,1000);
	glMatrixMode(GL_MODELVIEW);
	quad=gluNewQuadric();
	//initskybox();
	glEnable(GL_DEPTH_TEST);
	cam.setLocation(vector3d(10,10,10));	//the player will be top of the terrain
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	cam.Control();
	cam.UpdateCamera();
	glColor3f(0, 1, 0);
	gluSphere(quad, 5.0, 10, 10);
	for (int i = 0; i < bodies.size(); ++i)
	{
		if(bodies[i]->getCollisionShape()->getShapeType() == SPHERE_SHAPE_PROXYTYPE)
			renderSphere(bodies[i]);
		else if(bodies[i]->getCollisionShape()->getShapeType() == STATIC_PLANE_PROXYTYPE)
					renderPlane(bodies[i]);
	}

}


int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetVideoMode(640,480,32,SDL_OPENGL);
	Uint32 start;
	SDL_Event event;
	bool running=true;
	float angle=50;
	init(angle);
	while(running)
	{
		start=SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running=false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running=false;
							break;
						case SDLK_y:
							cam.mouseIn(false);
							break;
						case SDLK_SPACE:
						//if space is pressed, shoot a ball
							btRigidBody* sphere=addSphere(1.0,cam.getLocation().x,cam.getLocation().y,cam.getLocation().z,1.0);
							vector3d look=cam.getVector()*20;
							sphere->setLinearVelocity(btVector3(look.x,look.y,look.z));
							break;
					}
					break;
				case SDL_KEYUP:
					switch(event.key.keysym.sym)
					{

					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					cam.mouseIn(true);
					break;
				case SDLK_SPACE:
					btRigidBody* sphere = addSphere(10, cam.getLocation().x, cam.getLocation().y, cam.getLocation().z, 2.0);
					vector3d look = cam.getVector() * 2000;
					sphere->setLinearVelocity(btVector3(look.x, look.y, look.z));
					break;
			}
		}
		world->stepSimulation(1/60.0);
		display();
		SDL_GL_SwapBuffers();
		if(1000.0/60>SDL_GetTicks()-start)
			SDL_Delay(1000.0/60-(SDL_GetTicks()-start));
	}

	for(int i = 0; i < bodies.size(); i++)
	{
		world->removeCollisionObject(bodies[i]);
		btMotionState* motionState = bodies[i]->getMotionState();
		btCollisionShape* collisionShape = bodies[i]->getCollisionShape();
		delete bodies[i];
		delete collisionShape;
		delete motionState;
	}

	delete dispatcher;
	delete solver;
	delete broadphase;
	delete collisionConfig;
	delete world;
	SDL_Quit();
	gluDeleteQuadric(quad);
}
