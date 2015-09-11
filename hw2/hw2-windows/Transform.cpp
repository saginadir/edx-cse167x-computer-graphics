// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	vec3 nrml = glm::normalize(axis);
	float rad = degrees * pi / 180.0;
	return cos(rad) * mat3()
		+ (1 - cos(rad)) * mat3(nrml.x * nrml.x,
								nrml.x * nrml.y,
								nrml.x * nrml.z, nrml.x * nrml.y,
												 nrml.y * nrml.y,
												 nrml.y * nrml.z, nrml.z * nrml.x,
																  nrml.y * nrml.z,
																  nrml.z * nrml.z)
		+ sin(rad) * mat3(0, nrml.z, -nrml.y, -nrml.z, 0, nrml.x, nrml.y, -nrml.x, 0);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	eye = eye * rotate(-degrees, glm::normalize(up));
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 w = glm::normalize(glm::cross(eye, up));
	eye = eye * rotate(-degrees, w);
	up = up * rotate(-degrees, w);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 rot = mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, 0, 0, 0, 1);
	mat4 trans = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye.x, -eye.y, -eye.z, 1);

	return rot * trans;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	double d = 1 / glm::tan((fovy / 2) * (pi / 180));
	double a = -1 * ((zFar + zNear) / (zFar - zNear));
	double b = -1 * ((2 * zFar * zNear) / (zFar - zNear));
	return glm::transpose(mat4((d / aspect), 0, 0, 0,
										  0, d, 0, 0,
										  0, 0, a, b,
										  0, 0, -1, 0));
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	return mat4(sx, 0,  0,  0, 
		         0, sy, 0,  0, 
				 0, 0,  sz, 0, 
				 0, 0,  0,  1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
	return glm::transpose(mat4(1, 0, 0, tx,
							   0, 1, 0, ty,
							   0, 0, 1, tz,
							   0, 0, 0, 1));
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
