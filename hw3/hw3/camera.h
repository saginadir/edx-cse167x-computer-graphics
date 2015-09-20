#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera
{
public:
	Camera(float centerX, float centerY, float centerZ,
		   float lookAtX, float lookAtY, float lookAtZ,
		   float upX,     float upY,     float upZ,
		   int   fovy)
		   :center   (Vector(centerX, centerY, centerZ)),
			eye      (Vector(lookAtX, lookAtY, lookAtZ)),
			up       (Vector(upX, upY, upZ)),
			fovy     (fovy)
			{};
	
	Ray Camera::getRayThruPixel(const int &x, const int &y, const int &width, const int &height);

private:
	Vector center;	//look from
	Vector eye;		//look at
	Vector up;		//up direction of camera
	int fovy;
};

#endif