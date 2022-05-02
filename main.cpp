#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "quadTree.h"

#define PI 3.1415926

using namespace std;
double thetaComp = .5;
double G = 6.674e-11;

vector<Body*> bodies;
octTree* tree;
int currIndex;

int getRand(int min, int max) {
	return min + rand() % (max - min);	
}

void loadGalaxy() {
	tree = new octTree(10000, 0, 0);
	for(double i = 0; i < 2*PI; i += .004) {
		Body* tmp = new Body(pow(10, getRand(5, 15)), getRand(200, 500)*cos(i), getRand(200, 500)*sin(i), getRand(100, 150)*cos(i+PI/2), getRand(100, 150)*sin(i+PI/2));
		bodies.push_back(tmp);
		tree->addBody(tmp);
	}
	Body* center = new Body(8e20, 0, 0, 0, 0);
	bodies.push_back(center);
	tree->addBody(center);
}

void calcForce(Body* b, octTree* t, double dt) {
	double dist = sqrt(pow((t->xCenterMass - b->getX()), 2) + pow((t->yCenterMass - b->getY()), 2));
	if(!t->hasChildren || t->length/dist < thetaComp) {
		if(t->mass != 0 && dist > 0) {
			double force = b->getMass() * t->mass * G / pow(dist, 2);
			double theta = atan2(t->yCenterMass - b->getY(), t->xCenterMass - b->getX());
			double Fx = force*cos(theta);
			double Fy = force*sin(theta);
			double ax = Fx/b->getMass();
			double ay = Fy/b->getMass();
			b->setVx(b->getVx() + ax*dt);
			b->setVy(b->getVy() + ay*dt);
			b->setX(b->getX() + b->getVx()*dt);
			b->setY(b->getY() + b->getVy()*dt);
		}
	}
	else {
		calcForce(b, t->quadrants[0], dt);
		calcForce(b, t->quadrants[1], dt);
		calcForce(b, t->quadrants[2], dt);
		calcForce(b, t->quadrants[3], dt);
	}
}

void loop (int id) {
	double dt = .0005;
	for(int i = 0; i < bodies.size(); i++) {
		calcForce(bodies[i], tree, dt);
	}
	free(tree);
	tree = new octTree(10000, 0, 0);
	for(int i = 0; i < bodies.size(); i++) {
		tree->addBody(bodies[i]);
	}
	glutPostRedisplay();
}

void dispQuads(octTree* t) {
	glBegin(GL_LINE_LOOP);
	 glVertex2i(t->xOrigin - t->length/2, t->yOrigin - t->length/2);
	 glVertex2i(t->xOrigin + t->length/2, t->yOrigin - t->length/2);
	 glVertex2i(t->xOrigin + t->length/2, t->yOrigin + t->length/2);
	 glVertex2i(t->xOrigin - t->length/2, t->yOrigin + t->length/2);
	glEnd();
	if(t->hasChildren) {
		dispQuads(t->quadrants[0]);
		dispQuads(t->quadrants[1]);
		dispQuads(t->quadrants[2]);
		dispQuads(t->quadrants[3]);
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);	
	 for(int i = 0; i < bodies.size(); i++) {
		 glVertex2i(bodies[i]->getX(), bodies[i]->getY());
	 }
	glEnd();
	dispQuads(tree);
	glutTimerFunc((1/30)*1000, loop, 0);
	glFlush();
}

int main(int argc, char** argv) {
	srand(time(0));
	loadGalaxy();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Sequential N-Body");

	glClearColor(0,0,0,1);
	glColor3f(0,1,0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-780, 780, -420, 420);

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}
