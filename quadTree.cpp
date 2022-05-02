#include "octTree.h"

octTree::octTree(double length, double x, double y) {
	this->length = length;
	mass = 0;
	xCenterMass = 0;
	yCenterMass = 0;
	xOrigin = x;
	yOrigin = y;
	hasChildren = false;
}

void octTree::addBody(Body* n) {
	if(mass == 0) {
		bodies.push_back(n);
		mass = n->getMass();
		xCenterMass = n->getX();
		yCenterMass = n->getY();
	}
	else {
		//Add body to node, set new mass and center coordinates for node
		bodies.push_back(n);
		double totalMass = mass + n->getMass();
		xCenterMass = (mass*xCenterMass + n->getMass()*n->getX())/totalMass;
		yCenterMass = (mass*yCenterMass + n->getMass()*n->getX())/totalMass;
		mass = totalMass;
		if(hasChildren) {
		//if node has no children add body to proper quadrant
			double x = n->getX();
			double y = n->getY();
			
			bool xQuad = x > xOrigin;
			bool yQuad = y > yOrigin;

			if(xQuad && yQuad) { quadrants[0]->addBody(n); }
			else if(!xQuad && yQuad) { quadrants[1]->addBody(n); }
			else if(!xQuad && !yQuad) { quadrants[2]->addBody(n); }
			else if(xQuad && !yQuad) { quadrants[3]->addBody(n); }
			else {/*Body is at origin of quadrant (This is an issue)*/ exit(1); }
		}
		else {
		//Create child nodes and add all bodies in current node
			quadrants[0] = new octTree(length/2, xOrigin + length/4, yOrigin + length/4);
			quadrants[1] = new octTree(length/2, xOrigin - length/4, yOrigin + length/4);
			quadrants[2] = new octTree(length/2, xOrigin - length/4, yOrigin - length/4);
			quadrants[3] = new octTree(length/2, xOrigin + length/4, yOrigin - length/4);
			hasChildren = true;
			for(int i = 0; i < bodies.size(); i++) {
				double x = bodies[i]->getX();
				double y = bodies[i]->getY();
				
				bool xQuad = x > xOrigin;
				bool yQuad = y > yOrigin;

				if(xQuad && yQuad) { quadrants[0]->addBody(bodies[i]); }
				else if(!xQuad && yQuad) { quadrants[1]->addBody(bodies[i]); }
				else if(!xQuad && !yQuad) { quadrants[2]->addBody(bodies[i]); }
				else if(xQuad && !yQuad) { quadrants[3]->addBody(bodies[i]); }
				else {/*Body is at origin of quadrant (This is an issue)*/ exit(1); }
			}
		}
	}
}

void octTree::print() {
	cout << "Mass: " << mass << endl;
	cout << "Origin: (" << xOrigin << ", " << yOrigin << ")" << endl;
	cout << "Center of Mass: (" << xCenterMass << ", " << yCenterMass << ")" << endl;
	if(hasChildren) {
		quadrants[0]->print();
		quadrants[1]->print();
		quadrants[2]->print();
		quadrants[3]->print();
	}
}
