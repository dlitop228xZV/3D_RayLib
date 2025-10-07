#pragma once
#include "Curve.h"

class Ellipse : public Curve
{
private:
	double radiusX, radiusY;
public:
	Ellipse(double rx, double ry);
	Point3D GetPoint(double t) const override;
	Vector3D GetDerivative(double t) const override;
	double GetRadius() const override;
	void Draw(double t, const Point3D& position) const override;
};

