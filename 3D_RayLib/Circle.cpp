#include "Circle.h"
#include "Curve.h"
#include <raylib.h>
#include <math.h>
#include <iostream>

Circle::Circle(double r) : radius(r)
{
	if (r <= 0) std::cout << "!---Radius must be positive---!" << std::endl;
}

Point3D Circle::GetPoint(double t) const
{
    return Point3D{ (float)(radius * cos(t)), (float)(radius * sin(t)), 0.0 };
}

Vector3D Circle::GetDerivative(double t) const
{
    return Vector3D{ (float)(-radius * sin(t)), (float)(radius * cos(t)), 0.0 };
}

double Circle::GetRadius() const
{
	return radius;
}

void Circle::Draw(double t, const Point3D& position) const
{
	const int segments = 360;
	const float angleStep = 2 * PI / segments;

    for (int i = 0; i < segments; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = {
            (float)(position.x + radius * cos(angle1)),
            (float)(position.y + radius * sin(angle1)),
            (float)position.z
        };

        Vector3 v2 = {
            (float)(position.x + radius * cos(angle2)),
            (float)(position.y + radius * sin(angle2)),
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


