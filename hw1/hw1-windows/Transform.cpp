// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float rad = degrees * pi / 180.0;
	return cos(rad) * mat3() 
			+ (1 - cos(rad)) * mat3(axis.x * axis.x, 
									axis.x * axis.y, 
									axis.x * axis.z, axis.x * axis.y, 
													 axis.y * axis.y, 
													 axis.y * axis.z, axis.z * axis.x, 
																	  axis.y * axis.z, 
																	  axis.z * axis.z)
			+ sin(rad) * mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = eye * rotate(-degrees, glm::normalize(up));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 w = glm::normalize(glm::cross(eye, up));
	eye = eye * rotate(-degrees, w);
	up = up * rotate(-degrees, w);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 rot = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 trans = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);

	return rot * trans;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
