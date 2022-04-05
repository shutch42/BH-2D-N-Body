#include <iostream>
#include <math.h>
#include <vector>
#include "body.h"

class octTree {
	public:
		octTree(double length, double x, double y);
		void addBody(Body* n);
		void print();
		double length;
		double mass;
		double xCenterMass;
		double yCenterMass;
		double xOrigin;
		double yOrigin;
		vector<Body*> bodies;
		bool hasChildren;
		octTree* quadrants[4];
};
