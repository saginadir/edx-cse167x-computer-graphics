#ifndef CAMERA_H
#define CAMERA_H

#include <vec3.hpp>
#include "ray.h"

class Camera
{
public:
	Camera(float eyeX,    float eyeY,    float eyeZ,
		   float centerX, float centerY, float centerZ,
		   float upX,     float upY,     float upZ,
		   int   fovy)
		   :eye		 (glm::vec3(eyeX, eyeY, eyeZ)),
			center	 (glm::vec3(centerX, centerY, centerZ)),
			up		 (glm::vec3(upX, upY, upZ)),
			fovy     (fovy)
			{};
	
	Ray Camera::getRayThruPixel(const int &x, const int &y, const int &width, const int &height);

private:
	glm::vec3 eye;		//look from
	glm::vec3 center;	//look at
	glm::vec3 up;		//up direction of camera
	int fovy;
};

#endif