#include "triangle.h"
#include <glm.hpp>
#include <iostream>

IntersectInfo Triangle::intersect(Ray ray){
	glm::vec4 rayOrigTrans = glm::inverse(transform) * glm::vec4(ray.orig.x, ray.orig.y, ray.orig.z, 1);
	glm::vec4 rayDirnTrans = glm::inverse(transform) * ray.dirn;

	glm::vec3 rayOrigVec3 = glm::vec3(rayOrigTrans.x, rayOrigTrans.y, rayOrigTrans.z);
	glm::vec3 rayDirnVec3 = glm::vec3(rayDirnTrans.x, rayDirnTrans.y, rayDirnTrans.z);

	IntersectInfo info;
	
	glm::vec3 planeNormal = glm::normalize(glm::cross((c - a), (b - a)));

	//ray is parallel to triangle so it never intersects
	if (glm::dot(planeNormal, rayDirnVec3) == 0){
		info.isIntersect = false;
		info.distance = INFINITY;
		return info;
	}

	float t = (glm::dot(a, planeNormal) - glm::dot(planeNormal, rayOrigVec3)) / glm::dot(planeNormal, rayDirnVec3);
	glm::vec3 planeIntersect = rayOrigVec3 + rayDirnVec3 * t;

	float areaABC = glm::dot(glm::cross((b - a), (c - a)), planeNormal);

	float alpha, beta, gamma;
	alpha = glm::dot(glm::cross((c - b), (planeIntersect - b)), planeNormal) / areaABC;
	beta = glm::dot(glm::cross((a - c), (planeIntersect - c)), planeNormal) / areaABC;
	gamma = glm::dot(glm::cross((b - a), (planeIntersect - a)), planeNormal) / areaABC;

	if (alpha >= 0 && beta >= 0 && gamma >= 0 && alpha + beta + gamma == 1){
		info.isIntersect = true;

		glm::vec4 intersectTrans = transform * (rayOrigTrans + (rayDirnTrans * t));
		info.distance = intersectTrans.length();
	}
	else{
		info.isIntersect = false;
		info.distance = INFINITY;
	}

	return info;
}