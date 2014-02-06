////http://www.youtube.com/user/thecplusplusguy
////bullet physics tutorial 3, collision callback
//#include <iostream>
//#include <SDL/SDL.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
//#include "camera.h"
//#include <vector>
//#include <bullet/btBulletDynamicsCommon.h>
//
//using namespace std;
//
//struct bulletObject{
//	int id;
//	std::string name;
//	float r,g,b;
//	bool hit;
//	btRigidBody* body;
//	bulletObject(btRigidBody* b,int i,float r0,float g0,float b0) : body(b),id(i),r(r0),g(g0),b(b0),hit(false) {}
//};
//
//camera cam;
//GLUquadricObj* quad;
//btDynamicsWorld* world;
//btDispatcher* dispatcher;
//btCollisionConfiguration* collisionConfig;
//btBroadphaseInterface* broadphase;
//btConstraintSolver* solver;
//std::vector<bulletObject*> bodies;
//
//
//
//btRigidBody* addSphere(float rad,float x,float y,float z,float mass)
//{
//	btTransform t;
//	t.setIdentity();
//	t.setOrigin(btVector3(x,y,z));
//	btSphereShape* sphere=new btSphereShape(rad);
//	btVector3 inertia(0,0,0);
//	if(mass!=0.0)
//		sphere->calculateLocalInertia(mass,inertia);
//
//	btMotionState* motion=new btDefaultMotionState(t);
//	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
//	btRigidBody* body=new btRigidBody(info);
//	world->addRigidBody(body);
//	bodies.push_back(new bulletObject(body,0,1.0,0.0,0.0));
//	body->setUserPointer(bodies[bodies.size()-1]);
//	return body;
//}
//
//void renderSphere(bulletObject* bobj)
//{
//	bobj->name = "sphere";
//	btRigidBody* sphere=bobj->body;
//	if(sphere->getCollisionShape()->getShapeType()!=SPHERE_SHAPE_PROXYTYPE)
//		return;
//	if(!bobj->hit)
//		glColor3f(bobj->r,bobj->g,bobj->b);
//	else
//		glColor3f(1,0,0);
//
//	float r=((btSphereShape*)sphere->getCollisionShape())->getRadius();
//	btTransform t;
//	sphere->getMotionState()->getWorldTransform(t);
//	float mat[16];
//	t.getOpenGLMatrix(mat);
//	glPushMatrix();
//		glMultMatrixf(mat);	//translation,rotation
//		gluSphere(quad,r,20,20);
//	glPopMatrix();
//}
//
//btRigidBody* addCylinder(float d,float h,float x,float y,float z,float mass)
//{
//	btTransform t;
//	t.setIdentity();
//	t.setOrigin(btVector3(x,y,z));
//	btCylinderShape* sphere=new btCylinderShape(btVector3(d/2.0,h/2.0,d/2.0));
//	btVector3 inertia(0,0,0);
//	if(mass!=0.0)
//		sphere->calculateLocalInertia(mass,inertia);
//
//	btMotionState* motion=new btDefaultMotionState(t);
//	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
//	btRigidBody* body=new btRigidBody(info);
//	world->addRigidBody(body);
//	bodies.push_back(new bulletObject(body,1,0.0,1.0,0.0));
//	body->setUserPointer(bodies[bodies.size()-1]);
//	return body;
//}
//
//void renderCylinder(bulletObject* bobj)
//{
//	bobj->name = "cylinder";
//	btRigidBody* sphere=bobj->body;
//	if(sphere->getCollisionShape()->getShapeType()!=CYLINDER_SHAPE_PROXYTYPE)
//		return;
//	if(!bobj->hit)
//		glColor3f(bobj->r,bobj->g,bobj->b);
//	else
//		glColor3f(1,0,0);
//	btVector3 extent=((btCylinderShape*)sphere->getCollisionShape())->getHalfExtentsWithoutMargin();
//	btTransform t;
//	sphere->getMotionState()->getWorldTransform(t);
//	float mat[16];
//	t.getOpenGLMatrix(mat);
//	glPushMatrix();
//		glMultMatrixf(mat);	//translation,rotation
//		glTranslatef(0,extent.y(),0);
//		glRotatef(90,1,0,0);
//		gluCylinder(quad,extent.x(),extent.x(),extent.y()*2.0,20,20);
//	glPopMatrix();
//}
//
//btRigidBody* addCone(float d,float h,float x,float y,float z,float mass)
//{
//	btTransform t;
//	t.setIdentity();
//	t.setOrigin(btVector3(x,y,z));
//	btConeShape* sphere=new btConeShape(d,h);
//	btVector3 inertia(0,0,0);
//	if(mass!=0.0)
//		sphere->calculateLocalInertia(mass,inertia);
//
//	btMotionState* motion=new btDefaultMotionState(t);
//	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
//	btRigidBody* body=new btRigidBody(info);
//	world->addRigidBody(body);
//	bodies.push_back(new bulletObject(body,2,1.0,0.0,1.0));
//	body->setUserPointer(bodies[bodies.size()-1]);
//	return body;
//}
//
//void renderCone(bulletObject* bobj)
//{
//	bobj->name = "cone";
//	btRigidBody* sphere=bobj->body;
//	if(sphere->getCollisionShape()->getShapeType()!=CONE_SHAPE_PROXYTYPE)
//		return;
//	if(!bobj->hit)
//		glColor3f(bobj->r,bobj->g,bobj->b);
//	else
//		glColor3f(1,0,0);
//	float r=((btConeShape*)sphere->getCollisionShape())->getRadius();
//	float h=((btConeShape*)sphere->getCollisionShape())->getHeight();
//	btTransform t;
//	sphere->getMotionState()->getWorldTransform(t);
//	float mat[16];
//	t.getOpenGLMatrix(mat);
//	glPushMatrix();
//		glMultMatrixf(mat);	//translation,rotation
//		glTranslatef(0,h/2.0,0);
//		glRotatef(90,1,0,0);
//		gluCylinder(quad,0,r,h,20,20);
//	glPopMatrix();
//}
//
//btRigidBody* addBox(float width,float height,float depth,float x,float y,float z,float mass)
//{
//	btTransform t;
//	t.setIdentity();
//	t.setOrigin(btVector3(x,y,z));
//	btBoxShape* sphere=new btBoxShape(btVector3(width/2.0,height/2.0,depth/2.0));
//	btVector3 inertia(0,0,0);
//	if(mass!=0.0)
//		sphere->calculateLocalInertia(mass,inertia);
//
//	btMotionState* motion=new btDefaultMotionState(t);
//	btRigidBody::btRigidBodyConstructionInfo info(mass,motion,sphere,inertia);
//	btRigidBody* body=new btRigidBody(info);
//	world->addRigidBody(body);
//	bodies.push_back(new bulletObject(body,3,1.0,1.0,0.0));
//	body->setUserPointer(bodies[bodies.size()-1]);
//	return body;
//}
//
//void renderBox(bulletObject* bobj)
//{
//	bobj->name = "box";
//	btRigidBody* sphere=bobj->body;
//	if(sphere->getCollisionShape()->getShapeType()!=BOX_SHAPE_PROXYTYPE)
//		return;
//	if(!bobj->hit)
//		glColor3f(bobj->r,bobj->g,bobj->b);
//	else
//		glColor3f(1,0,0);
//	btVector3 extent=((btBoxShape*)sphere->getCollisionShape())->getHalfExtentsWithoutMargin();
//	btTransform t;
//	sphere->getMotionState()->getWorldTransform(t);
//	float mat[16];
//	t.getOpenGLMatrix(mat);
//	glPushMatrix();
//		glMultMatrixf(mat);	//translation,rotation
//		glBegin(GL_QUADS);
//			glVertex3f(-extent.x(),extent.y(),-extent.z());
//			glVertex3f(-extent.x(),-extent.y(),-extent.z());
//			glVertex3f(-extent.x(),-extent.y(),extent.z());
//			glVertex3f(-extent.x(),extent.y(),extent.z());
//		glEnd();
//		glBegin(GL_QUADS);
//			glVertex3f(extent.x(),extent.y(),-extent.z());
//			glVertex3f(extent.x(),-extent.y(),-extent.z());
//			glVertex3f(extent.x(),-extent.y(),extent.z());
//			glVertex3f(extent.x(),extent.y(),extent.z());
//		glEnd();
//		glBegin(GL_QUADS);
//			glVertex3f(-extent.x(),extent.y(),extent.z());
//			glVertex3f(-extent.x(),-extent.y(),extent.z());
//			glVertex3f(extent.x(),-extent.y(),extent.z());
//			glVertex3f(extent.x(),extent.y(),extent.z());
//		glEnd();
//		glBegin(GL_QUADS);
//			glVertex3f(-extent.x(),extent.y(),-extent.z());
//			glVertex3f(-extent.x(),-extent.y(),-extent.z());
//			glVertex3f(extent.x(),-extent.y(),-extent.z());
//			glVertex3f(extent.x(),extent.y(),-extent.z());
//		glEnd();
//		glBegin(GL_QUADS);
//			glVertex3f(-extent.x(),extent.y(),-extent.z());
//			glVertex3f(-extent.x(),extent.y(),extent.z());
//			glVertex3f(extent.x(),extent.y(),extent.z());
//			glVertex3f(extent.x(),extent.y(),-extent.z());
//		glEnd();
//		glBegin(GL_QUADS);
//			glVertex3f(-extent.x(),-extent.y(),-extent.z());
//			glVertex3f(-extent.x(),-extent.y(),extent.z());
//			glVertex3f(extent.x(),-extent.y(),extent.z());
//			glVertex3f(extent.x(),-extent.y(),-extent.z());
//		glEnd();
//	glPopMatrix();
//}
//
//void renderPlane(bulletObject* bobj)
//{
//	bobj->name = "plane";
//	btRigidBody* plane=bobj->body;
//	if(plane->getCollisionShape()->getShapeType()!=STATIC_PLANE_PROXYTYPE)
//		return;
//	if(!bobj->hit)
//		glColor3f(bobj->r,bobj->g,bobj->b);
//	else
//		glColor3f(1,0,0);
//	btTransform t;
//	plane->getMotionState()->getWorldTransform(t);
//	float mat[16];
//	t.getOpenGLMatrix(mat);
//	glPushMatrix();
//		glMultMatrixf(mat);	//translation,rotation
//		glBegin(GL_QUADS);
//			glVertex3f(-1000,0,1000);
//			glVertex3f(-1000,0,-1000);
//			glVertex3f(1000,0,-1000);
//			glVertex3f(1000,0,1000);
//		glEnd();
//	glPopMatrix();
//}
//
//
//void init(float angle)
//{
//	collisionConfig=new btDefaultCollisionConfiguration();
//	dispatcher=new btCollisionDispatcher(collisionConfig);
//	broadphase=new btDbvtBroadphase();
//	solver=new btSequentialImpulseConstraintSolver();
//	world=new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfig);
//	world->setGravity(btVector3(0,-10,0));
//
//	btTransform t;
//	t.setIdentity();
//	t.setOrigin(btVector3(0,0,0));
//	btStaticPlaneShape* plane=new btStaticPlaneShape(btVector3(0,1,0),0);
//	btMotionState* motion=new btDefaultMotionState(t);
//	btRigidBody::btRigidBodyConstructionInfo info(0.0,motion,plane);
//	btRigidBody* body=new btRigidBody(info);
//	world->addRigidBody(body);
//	bodies.push_back(new bulletObject(body,4,0.8,0.8,0.8));
//	body->setUserPointer(bodies[bodies.size()-1]);
//
//	addSphere(1.0,0,20,0,1.0);
//
//	glClearColor(0,0,0,1);
//	glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluPerspective(angle,640.0/480.0,1,1000);
//	glMatrixMode(GL_MODELVIEW);
//	quad=gluNewQuadric();
//	//initskybox();
//	glEnable(GL_DEPTH_TEST);
//	cam.setLocation(vector3d(10,10,10));	//the player will be top of the terrain
//}
//
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
//	cam.Control();
//	//drawSkybox(50);
//	cam.UpdateCamera();
//
//
//	for(int i=0;i<bodies.size();i++)
//	{
//		if(bodies[i]->body->getCollisionShape()->getShapeType()==STATIC_PLANE_PROXYTYPE)
//			renderPlane(bodies[i]);
//		else if(bodies[i]->body->getCollisionShape()->getShapeType()==SPHERE_SHAPE_PROXYTYPE)
//			renderSphere(bodies[i]);
//		else if(bodies[i]->body->getCollisionShape()->getShapeType()==CYLINDER_SHAPE_PROXYTYPE)
//			renderCylinder(bodies[i]);
//		else if(bodies[i]->body->getCollisionShape()->getShapeType()==CONE_SHAPE_PROXYTYPE)
//			renderCone(bodies[i]);
//		else if(bodies[i]->body->getCollisionShape()->getShapeType()==BOX_SHAPE_PROXYTYPE)
//			renderBox(bodies[i]);
//	}
//}
//
//bool callbackFunc(btManifoldPoint& cp,const btCollisionObjectWrapper* obj1,int id1,int index1,const btCollisionObjectWrapper* obj2,int id2,int index2)
//{
//	((bulletObject*)obj1->getCollisionObject()->getUserPointer())->hit=true;
//
//	((bulletObject*)obj2->getCollisionObject()->getUserPointer())->hit=true;
//	cout << ((bulletObject*)obj1->getCollisionObject()->getUserPointer())->name <<
//			" hit by " << ((bulletObject*)obj2->getCollisionObject()->getUserPointer())->name << endl;
//
//	return false;
//}
//
//int main()
//{
//	SDL_Init(SDL_INIT_EVERYTHING);
//	SDL_SetVideoMode(640,480,32,SDL_OPENGL);
//	Uint32 start;
//	SDL_Event event;
//	bool running=true;
//	float angle=50;
//	init(angle);
//	gContactAddedCallback=callbackFunc;
//	addCylinder(2,5,0,30,0,1.0);
//	addCone(2,5,5,30,0,1.0);
//	addBox(10,2,3,0,40,0,1.0);
//	while(running)
//	{
//		start=SDL_GetTicks();
//		while(SDL_PollEvent(&event))
//		{
//			switch(event.type)
//			{
//				case SDL_QUIT:
//					running=false;
//					break;
//				case SDL_KEYDOWN:
//					switch(event.key.keysym.sym)
//					{
//						case SDLK_ESCAPE:
//							running=false;
//							break;
//						case SDLK_y:
//							cam.mouseIn(false);
//							break;
//						case SDLK_SPACE:
//							btRigidBody* sphere=addSphere(1.0,cam.getLocation().x,cam.getLocation().y,cam.getLocation().z,1.0);
//							vector3d look=cam.getVector()*20;
//							sphere->setLinearVelocity(btVector3(look.x,look.y,look.z));
//							sphere->setCollisionFlags(sphere->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
//							break;
//					}
//					break;
//				case SDL_KEYUP:
//					switch(event.key.keysym.sym)
//					{
//
//					}
//					break;
//				case SDL_MOUSEBUTTONDOWN:
//					cam.mouseIn(true);
//					break;
//
//			}
//		}
//		for(int i=0;i<bodies.size();i++)
//			bodies[i]->hit=false;
//		world->stepSimulation(1/60.0);
//		display();
//		SDL_GL_SwapBuffers();
//		if(1000.0/60>SDL_GetTicks()-start)
//			SDL_Delay(1000.0/60-(SDL_GetTicks()-start));
//	}
//	//killskybox();
//	for(int i=0;i<bodies.size();i++)
//	{
//		world->removeCollisionObject(bodies[i]->body);
//		btMotionState* motionState=bodies[i]->body->getMotionState();
//		btCollisionShape* shape=bodies[i]->body->getCollisionShape();
//		delete bodies[i]->body;
//		delete shape;
//		delete motionState;
//		delete bodies[i];
//	}
//	delete dispatcher;
//	delete collisionConfig;
//	delete solver;
//	delete broadphase;
//	delete world;
//	SDL_Quit();
//	gluDeleteQuadric(quad);
//}
