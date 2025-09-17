#pragma once
#include "Curve.h"
class Helixes : protected Curve
{
private:
	double radius, step;
public:
	Helixes(double r, double s);
	Point3D GetPoint(double t) const override;
	Vector3D GetDerivative(double t) const override;
	double GetRadius() const override;
	void Draw(double t, const Point3D& position) const override;
};


