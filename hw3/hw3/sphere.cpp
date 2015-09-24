#include "sphere.h"
#include <cmath>
#include <glm.hpp>

IntersectInfo Sphere::intersect(Ray ray)
{
	glm::vec3 rayToSphereCenter = ray.orig - pos;

	// coefficients of a quadratic equation ax^2 + bx + c = 0
	
	float a = glm::dot(ray.dirn, ray.dirn);
	float b = 2 * glm::dot(ray.dirn, rayToSphereCenter);
	float c = glm::dot(rayToSphereCenter, rayToSphereCenter) - (radius * radius);

	float discr = (b*b) - (4*a*c); //discriminant of a quadratic equation

	IntersectInfo info;

	//check discriminant
	if (discr < 0){
		info.isIntersect = false;
		info.distance = INFINITY;
	}
	else{
		info.isIntersect = true;

		float t1, t2;
		t1 = (-b + sqrt(discr)) / (2 * a);
		t2 = (-b - sqrt(discr)) / (2 * a);

		if (t1 <= t2){
			info.distance = (ray.orig + (ray.dirn * t1)).length();
		}
		else{
			info.distance = (ray.orig + (ray.dirn * t2)).length();
		}
	}

	return info;
}