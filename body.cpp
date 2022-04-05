#include "body.h"

Body::Body(double mass, double x, double y, double vx, double vy) {
	this->mass = mass;	
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

void Body::print() {
	cout << "Mass: " << mass << endl;
	cout << "Position: (" << x << ", " << y << ")" << endl;
	cout << "Velocity: (" << vx << ", " << vy << ")" << endl;
}

void Body::setMass(double mass) {
	this->mass = mass;
}

void Body::setX(double x) {
	this->x = x;
}

void Body::setY(double y) {
	this->y = y;
}

void Body::setVx(double vx) {
	this->vx = vx;
}

void Body::setVy(double vy) {
	this->vy = vy;
}

double Body::getMass() {
	return mass;
}

double Body::getX() {
	return x;
}

double Body::getY() {
	return y;
}

double Body::getVx() {
	return vx;
}

double Body::getVy() {
	return vy;
}
