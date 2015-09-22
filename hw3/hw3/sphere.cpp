#include "sphere.h"
#include <cmath>

IntersectInfo Sphere::intersect(Ray ray)
{
	Vector rayToSphereCenter = ray.orig - pos;

	// coefficients of a quadratic equation ax^2 + bx + c = 0
	float a = ray.dirn.dot(ray.dirn);
	float b = 2 * (ray.dirn.dot(rayToSphereCenter));
	float c = rayToSphereCenter.dot(rayToSphereCenter) - (radius * radius);

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
			info.distance = (ray.orig + (ray.dirn * t1)).magnitude();
		}
		else{
			info.distance = (ray.orig + (ray.dirn * t2)).magnitude();
		}
	}

	return info;
}