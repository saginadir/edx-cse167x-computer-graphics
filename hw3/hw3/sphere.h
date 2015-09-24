#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive{
public:
	Sphere() :pos(glm::vec3()), radius(1){};
	Sphere(int x, int y, int z, float radius) :pos(glm::vec3(x, y, z)), radius(radius){};
	virtual ~Sphere(){};
	virtual IntersectInfo intersect(Ray ray);

	glm::vec3 pos;
	float radius;
};

#endif