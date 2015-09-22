#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive{
public:
	Sphere() :pos(Vector()), radius(1){};
	Sphere(int x, int y, int z, float radius) :pos(Vector(x,y,z)), radius(radius){};
	virtual ~Sphere(){};
	virtual IntersectInfo intersect(Ray ray);

	Vector pos;
	float radius;
};

#endif