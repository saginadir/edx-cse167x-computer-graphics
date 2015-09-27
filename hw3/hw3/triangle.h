#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "primitive.h"
#include <vec3.hpp>

class Triangle : public Primitive
{
public:
	Triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c) :a(a), b(b), c(c){};
	virtual ~Triangle(){};
	virtual IntersectInfo intersect(Ray ray);
	glm::vec3 a, b, c;
};

#endif