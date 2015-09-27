#include "sphere.h"
#include <cmath>
#include <glm.hpp>

IntersectInfo Sphere::intersect(Ray ray)
{
	glm::vec4 rayOrigTrans = glm::inverse(transform) * glm::vec4(ray.orig.x, ray.orig.y, ray.orig.z, 1);
	glm::vec4 rayDirnTrans = glm::inverse(transform) * ray.dirn;

	glm::vec4 rayToSphereCenter = rayOrigTrans - (transform * glm::vec4(pos.x, pos.y, pos.z, 1));

	// coefficients of a quadratic equation ax^2 + bx + c = 0
	
	float a = glm::dot(rayDirnTrans, rayDirnTrans);
	float b = 2 * glm::dot(rayDirnTrans, rayToSphereCenter);
	float c = glm::dot(rayToSphereCenter, rayToSphereCenter) - (radius * radius);

	float discr = (b*b) - (4*a*c); //discriminant of a quadratic equation

	IntersectInfo info;

	//negative discriminant means complex roots (no intersection)
	if (discr < 0){
		info.isIntersect = false;
		info.distance = INFINITY;
	}
	else{
		info.isIntersect = true;

		float t1, t2;
		t1 = (-b + sqrt(discr)) / (2 * a);
		t2 = (-b - sqrt(discr)) / (2 * a);

		glm::vec4 intersectTrans;

		//if either root is negative, use the positive root
		if (t1 < 0 || t2 < 0){
			if (t1 < 0){
				intersectTrans = transform * (rayOrigTrans + (rayDirnTrans * t2));
				info.distance = intersectTrans.length();
			}
			else if (t2 < 0){
				intersectTrans = transform * (rayOrigTrans + (rayDirnTrans * t1));
				info.distance = intersectTrans.length();
			}
		}
		//both positive then pick the smallest
		else{
			if (t1 <= t2){
				intersectTrans = transform * (rayOrigTrans + (rayDirnTrans * t1));
				info.distance = intersectTrans.length();
			}
			else{
				intersectTrans = transform * (rayOrigTrans + (rayDirnTrans * t2));
				info.distance = intersectTrans.length();
			}
		}
	}

	return info;
}