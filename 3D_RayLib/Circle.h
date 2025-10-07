#pragma once
#include "Curve.h"
class Circle : public Curve
{
private:
	double radius;
public:
	Circle(double r);
	Point3D GetPoint(double t) const override;
	Vector3D GetDerivative(double t) const override;
	double GetRadius() const override;
	void Draw(double t, const Point3D& position) const override;
};

