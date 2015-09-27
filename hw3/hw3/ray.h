#ifndef RAY_H
#define RAY_H

#include <vec4.hpp>

class Ray{
public:
	Ray(glm::vec4 orig, glm::vec4 dirn) :orig(orig), dirn(dirn){};
	
	glm::vec4 orig;
	glm::vec4 dirn;
};

#endif