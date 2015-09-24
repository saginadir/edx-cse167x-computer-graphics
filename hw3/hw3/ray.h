#ifndef RAY_H
#define RAY_H

#include <vec3.hpp>

class Ray{
public:
	Ray() :orig(glm::vec3()), dirn(glm::vec3()){};
	Ray(glm::vec3 orig, glm::vec3 dirn) :orig(orig), dirn(dirn){};
	
	glm::vec3 orig;
	glm::vec3 dirn;
};

#endif