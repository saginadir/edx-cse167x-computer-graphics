#include "camera.h"

#define _USE_MATH_DEFINES //for M_PI constant
#include <cmath>
#include <glm.hpp>

Ray Camera::getRayThruPixel(const int &x, const int &y, const int &width, const int &height){
	double fovyRads, fovxRads; //fovy is provided, but fovx has to be calculated
	double alpha, beta; //used to compute ray direction
	double xCenter, yCenter; //auto grader sends rays through the center of a pixel
	glm::vec3 u, v, w; //orthonormal basis for the camera
	
	fovyRads = fovy * M_PI / 180;
	fovxRads = 2 * atan(tan(fovyRads / 2) * ((float) width / (float) height));

	xCenter = x + 0.5;
	yCenter = y + 0.5;

	w = glm::normalize(eye - center);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);

	alpha = tan(fovxRads/2) * ((xCenter - (width / 2)) / (width / 2));
	beta = tan(fovyRads/2) * (((height / 2) - yCenter) / (height / 2));

	glm::vec3 dirn = glm::normalize((u * (float)alpha + v * (float)beta - w));

	return Ray(eye, dirn);
}