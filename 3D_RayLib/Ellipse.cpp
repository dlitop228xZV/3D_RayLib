#include "Ellipse.h"
#include <raylib.h>
#include <cmath>
#include <iostream>

Ellipse::Ellipse(double rx, double ry) : radiusX(rx), radiusY(ry)
{
    if (rx <= 0) std::cout << "!---Radius X must be positive---!" << std::endl;
    if (ry <= 0) std::cout << "!---Radius Y must be positive---!" << std::endl;
}

Point3D Ellipse::GetPoint(double t) const
{
    return { (float)(radiusX * cos(t)), (float)(radiusY * sin(t)), 0.0f };
}

Vector3D Ellipse::GetDerivative(double t) const
{
    return { (float)(-radiusX * sin(t)), (float)(radiusY * cos(t)), 0.0f };
}

double Ellipse::GetRadius() const
{
    return (radiusX + radiusY) / 2.0;
}

void Ellipse::Draw(double t, const Point3D& position, float rotationAngle) const
{
    const int segments = 360;
    const float angleStep = 2 * PI / segments;

    auto RotateY = [](const Vector3& point, float angleDeg, const Vector3& center) -> Vector3 {
        float rad = angleDeg * (PI / 180.0f);
        float cosA = cos(rad);
        float sinA = sin(rad);

        float x = point.x - center.x;
        float z = point.z - center.z;

        float xr = x * cosA - z * sinA + center.x;
        float zr = x * sinA + z * cosA + center.z;

        return { xr, point.y, zr };
        };

    for (int i = 0; i < segments; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = { position.x + (float)(radiusX * cos(angle1)),
                       position.y + (float)(radiusY * sin(angle1)),
                       position.z };
        Vector3 v2 = { position.x + (float)(radiusX * cos(angle2)),
                       position.y + (float)(radiusY * sin(angle2)),
                       position.z };

        v1 = RotateY(v1, rotationAngle, position);
        v2 = RotateY(v2, rotationAngle, position);

        DrawLine3D(v1, v2, GREEN);
    }

    Point3D current = GetPoint(t);
    Vector3 pointPos = { position.x + current.x, position.y + current.y, position.z + current.z };
    pointPos = RotateY(pointPos, rotationAngle, position);

    DrawSphere(pointPos, 0.1f, RED);

    Vector3D derivative = GetDerivative(t);
    Vector3 endPoint = { pointPos.x + derivative.x * 0.3f,
                         pointPos.y + derivative.y * 0.3f,
                         pointPos.z + derivative.z * 0.3f };
    endPoint = RotateY(endPoint, rotationAngle, position);

    DrawLine3D(pointPos, endPoint, BLACK);
}
