#include "vector.h"
#include <cmath>

Vector Vector::operator=(const Vector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

Vector Vector::operator+(const Vector &b) const
{
	Vector c;
	c.x = x + b.x;
	c.y = y + b.y;
	c.z = z + b.z;
	return c;
}

Vector Vector::operator-(const Vector &b) const
{
	Vector c;
	c.x = x - b.x;
	c.y = y - b.y;
	c.z = z - b.z;
	return c;
}

Vector Vector::operator*(const float &f) const
{
	Vector s;
	s.x = x * f;
	s.y = y * f;
	s.z = z * f;
	return s;
}

Vector Vector::operator*(const double &d) const
{
	Vector s;
	s.x = (float)(x * d);
	s.y = (float)(y * d);
	s.z = (float)(z * d);
	return s;
}

float Vector::magnitude() const
{
	return sqrt(x*x + y*y + z*z);
}

Vector Vector::normalized() const
{
	float mag = magnitude();
	Vector n;
	n.x = x / mag;
	n.y = y / mag;
	n.z = z / mag;
	return n;
}

float Vector::dot(const Vector &v) const{
	float dot = 0;
	dot += x * v.x;
	dot += y * v.y;
	dot += z * v.z;
	return dot;
}

Vector Vector::cross(const Vector &b) const
{
	Vector c;
	c.x = y * b.z - z * b.y;
	c.y = z * b.x - x * b.z;
	c.z = x * b.y - y * b.x;
	return c;
}