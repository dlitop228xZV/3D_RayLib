#pragma once
#include <raylib.h>

#define M_PI 3.14159265358979323846

struct Point3D
{
	double x, y, z;
	Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
};

struct Vector3D {
	double x, y, z;
	Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

class Curve
{	
public:
	virtual ~Curve() = default;
	virtual double GetRadius() const = 0;
	virtual Point3D GetPoint(double t) const = 0;
	virtual Vector3D GetDerivative(double t) const = 0;
	virtual void Draw(double t, const Point3D& pos) const = 0;
};