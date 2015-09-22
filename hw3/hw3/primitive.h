#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"

struct IntersectInfo{
	bool isIntersect;
	float distance;
};

class Primitive
{
public:
	virtual ~Primitive(){};
	virtual IntersectInfo intersect(Ray ray) = 0;
};

#endif