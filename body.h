#include <iostream>
using namespace std;

class Body {
	public:
		Body(double mass, double x, double y, double vx, double vy);
		void print();
		void setMass(double mass);
		void setX(double x);
		void setY(double y);
		void setVx(double vx);
		void setVy(double vy);
		double getMass();
		double getX();
		double getY();
		double getVx();
		double getVy();
	private:
		double mass;
		double x;
		double y;
		double vx;
		double vy;
};
