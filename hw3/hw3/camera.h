#ifndef CAMERA_H
#define CAMERA_H

#include "vector.h"
#include "ray.h"

class Camera
{
public:
	Camera(float eyeX,    float eyeY,    float eyeZ,
		   float centerX, float centerY, float centerZ,
		   float upX,     float upY,     float upZ,
		   int   fovy)
		   :eye		 (Vector(eyeX, eyeY, eyeZ)),
			center   (Vector(centerX, centerY, centerZ)),
			up       (Vector(upX, upY, upZ)),
			fovy     (fovy)
			{};
	
	Ray Camera::getRayThruPixel(const int &x, const int &y, const int &width, const int &height);

private:
	Vector eye;		//look from
	Vector center;	//look at
	Vector up;		//up direction of camera
	int fovy;
};

#endif