#include "Ellipse.h"
#include "Curve.h"
#include <raylib.h>
#include <math.h>
#include <iostream>

Ellipse::Ellipse(double rx, double ry)
{
    if (rx <= 0) std::cout << "!---Radius X must be positive---!" << std::endl;
    if (ry <= 0) std::cout << "!---Radius Y must be positive---!" << std::endl;
}

Point3D Ellipse::GetPoint(double t) const
{
    return Point3D{ (float)(radiusX * cos(t)), (float)(radiusY * sin(t)), 0.0 };
}

Vector3D Ellipse::GetDerivative(double t) const
{
    return Vector3D{ (float)(-radiusX * sin(t)), (float)(radiusY * cos(t)), 0.0 };
}

double Ellipse::GetRadius() const
{
    return (radiusX + radiusY) / 2; // Средний радиус
}

void Ellipse::Draw(double t, const Point3D& position) const
{
    const int segments = 360;
    const float angleStep = 2 * PI / segments;

    for (int i = 0; i < segments; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = {
            (float)(position.x + radiusX * cos(angle1)),
            (float)(position.y + radiusY * sin(angle1)),
            (float)position.z
        };

        Vector3 v2 = {
            (float)(position.x + radiusX * cos(angle2)),
            (float)(position.y + radiusY * sin(angle2)),
            (float)position.z
        };

        DrawLine3D(v1, v2, BLUE);
    }

    Point3D current = GetPoint(t);
    Vector3 pointPos = {
        (float)(position.x + current.x),
        (float)(position.y + current.y),
        (float)(position.z + current.z)
    };

    DrawSphere(pointPos, 0.1f, RED);

    Vector3D derivative = GetDerivative(t);
    Vector3 endPoint = {
        (float)(pointPos.x + derivative.x * 0.3),
        (float)(pointPos.y + derivative.y * 0.3),
        (float)(pointPos.z + derivative.z * 0.3)
    };
}


