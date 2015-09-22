#ifndef VECTOR_H_
#define VECTOR_H_

class Vector
{
public:
	Vector() :x(0), y(0), z(0){};
	Vector(const float &x, const float &y, const float &z) :x(x), y(y), z(z){};

	Vector operator=(const Vector &v);
	Vector operator+(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator*(const float &f) const;
	Vector operator*(const double &d) const;

	float magnitude() const;
	Vector normalized() const;
	float dot(const Vector &v) const;
	Vector cross(const Vector &v) const;

	float x, y, z;
};

#endif