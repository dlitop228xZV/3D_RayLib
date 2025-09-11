#pragma once
#include <raylib.h>

#define M_PI 3.14159265358979323846

typedef Vector3 Point3D;
typedef Vector3 Vector3D;

class Curve
{	
public:
	virtual ~Curve() = default;
	virtual double GetRadius() const = 0;
	virtual Point3D GetPoint(double t) const = 0;
	virtual Vector3D GetDerivative(double t) const = 0;
	virtual void Draw(double t, const Point3D& pos) const = 0;
};