#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive{
public:
	Sphere(int x, int y, int z, float radius) :pos(glm::vec4(x, y, z, 0)), radius(radius){};
	virtual ~Sphere(){};
	virtual IntersectInfo intersect(Ray ray);

	glm::vec4 pos;
	float radius;
};

#endif