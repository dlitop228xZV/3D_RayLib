#pragma once
#include <raylib.h>

#define M_PI 3.14159265358979323846

typedef Vector3 Point3D;
typedef Vector3 Vector3D;

class Curve
{
protected:
    float rotationAngle = 0;
    Vector3 rotationAxis = { 0, 1, 0 };
public:
    virtual ~Curve() = default;

    virtual double GetRadius() const = 0;
    virtual Point3D GetPoint(double t) const = 0;
    virtual Vector3D GetDerivative(double t) const = 0;
    virtual void Draw(double t, const Point3D& pos, float rotationAngle = 0, const Vector3& rotationAxis = { 0, 1, 0 }) const = 0;
    void SetRotation(float angle, const Vector3& axis = { 0, 1, 0 }) {
        rotationAngle = angle;
        rotationAxis = axis;
    }
};
