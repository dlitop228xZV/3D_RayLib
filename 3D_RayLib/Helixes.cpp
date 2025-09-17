#include "Helixes.h"
#include "Curve.h"
#include <raylib.h>
#include <math.h>
#include <iostream>

Helixes::Helixes(double r, double s) : radius(r), step(s)
{
    if (r <= 0) std::cout << "!---Radius must be positive---!" << std::endl;
}

Point3D Helixes::GetPoint(double t) const
{
    return Point3D{ (float)(radius * cos(t)), (float)(radius * sin(t)), (float)(step * t / (2 * M_PI)) };
}

Vector3D Helixes::GetDerivative(double t) const
{
    return Vector3D{ (float)(-radius * sin(t)), (float)(radius * cos(t)), (float)(step * t / (2 * M_PI)) };
}

double Helixes::GetRadius() const
{
    return radius;
}

void Helixes::Draw(double t, const Point3D& position) const
{
    const int segments = 720;
    const int turns = 2;
    const float angleStep = 2 * PI / segments;

    for (int i = 0; i < segments * turns; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = {
            (float)(position.x + radius * cos(angle1)),
            (float)(position.y + radius * sin(angle1)),
            (float)position.z + step * angle1 / (2 * M_PI)
        };

        Vector3 v2 = {
            (float)(position.x + radius * cos(angle2)),
            (float)(position.y + radius * sin(angle2)),
            (float)position.z + step * angle1 / (2 * M_PI)
        };

        DrawLine3D(v1, v2, ORANGE);
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


