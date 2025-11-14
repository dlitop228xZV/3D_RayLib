#pragma once
#include "Curve.h"

class Circle : public Curve {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}

    Point3D GetPoint(double t) const override;
    Vector3D GetDerivative(double t) const override;
    double GetRadius() const override;
    void Draw(double t, const Point3D& position, float rotationAngle = 0, const Vector3& rotationAxis = { 0, 1, 0 }) const override;
};
