#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <string>

class Vector
{
	public:
		Vector() :x(0), y(0), z(0){};
		Vector(float x, float y, float z) :x(x), y(y), z(z){};

	private:
		float x, y, z;
};

#endif