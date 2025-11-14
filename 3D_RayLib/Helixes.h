#pragma once
#include "Curve.h"

class Helixes : public Curve
{
private:
    double radius, step;
public:
    Helixes(double r, double s);
    Point3D GetPoint(double t) const override;
    Vector3D GetDerivative(double t) const override;
    double GetRadius() const override;
    void Draw(double t, const Point3D& position, float rotationAngle = 0, const Vector3& rotationAxis = { 0, 1, 0 }) const override;
};