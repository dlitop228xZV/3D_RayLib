#include "Helixes.h"
#include <raylib.h>
#include <cmath>
#include <iostream>

Helixes::Helixes(double r, double s) : radius(r), step(s)
{
    if (r <= 0) std::cout << "!---Radius must be positive---!" << std::endl;
}

Point3D Helixes::GetPoint(double t) const
{
    return { (float)(radius * cos(t)),
             (float)(radius * sin(t)),
             (float)(step * t / (2 * M_PI)) };
}

Vector3D Helixes::GetDerivative(double t) const
{
    return { (float)(-radius * sin(t)),
             (float)(radius * cos(t)),
             (float)(step / (2 * M_PI)) };
}

double Helixes::GetRadius() const
{
    return 0.0;
}

void Helixes::Draw(double t, const Point3D& position, float rotationAngle) const
{
    const int segments = 720;
    const int turns = 2;
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

    // Рисуем саму спираль
    for (int i = 0; i < segments * turns; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = { position.x + (float)(radius * cos(angle1)),
                       position.y + (float)(radius * sin(angle1)),
                       position.z + (float)(step * angle1 / (2 * M_PI)) };
        Vector3 v2 = { position.x + (float)(radius * cos(angle2)),
                       position.y + (float)(radius * sin(angle2)),
                       position.z + (float)(step * angle2 / (2 * M_PI)) };

        v1 = RotateY(v1, rotationAngle, position);
        v2 = RotateY(v2, rotationAngle, position);

        DrawLine3D(v1, v2, ORANGE);
    }

    // Рисуем шар в текущей точке t
    Point3D current = GetPoint(t);
    Vector3 pointPos = { position.x + current.x, position.y + current.y, position.z + current.z };
    pointPos = RotateY(pointPos, rotationAngle, position);

    DrawSphere(pointPos, 0.1f, RED);

    // Рисуем производную (касательный вектор)
    Vector3D derivative = GetDerivative(t);
    Vector3 endPoint = { pointPos.x + derivative.x * 0.3f,
                         pointPos.y + derivative.y * 0.3f,
                         pointPos.z + derivative.z * 0.3f };
    endPoint = RotateY(endPoint, rotationAngle, position);

    DrawLine3D(pointPos, endPoint, BLACK);
}