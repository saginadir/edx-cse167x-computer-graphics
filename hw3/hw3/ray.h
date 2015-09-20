#ifndef RAY_H
#define RAY_H

#include "vector.h"

class Ray{
public:
	Ray():orig(Vector()), dirn(Vector()){};
	Ray(Vector orig, Vector dirn) :orig(orig), dirn(dirn){};

private:
	Vector orig;
	Vector dirn;
};

#endif