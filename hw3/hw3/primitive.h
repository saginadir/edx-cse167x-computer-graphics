#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "ray.h"
#include <glm.hpp>

struct IntersectInfo{
	bool isIntersect;
	float distance;
};

class Primitive
{
public:
	virtual ~Primitive(){};
	virtual IntersectInfo intersect(Ray ray) = 0;

	glm::mat4 transform;
	glm::vec3 emission;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;
};

#endif