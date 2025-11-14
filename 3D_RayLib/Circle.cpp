#include "Circle.h"
#include <raylib.h>
#include <cmath>
#include <iostream>

Point3D Circle::GetPoint(double t) const
{
    return { (float)(radius * cos(t)), (float)(radius * sin(t)), 0.0f };
}

Vector3D Circle::GetDerivative(double t) const
{
    return { (float)(-radius * sin(t)), (float)(radius * cos(t)), 0.0f };
}

double Circle::GetRadius() const
{
    return radius;
}

void Circle::Draw(double t, const Point3D& position, float rotationAngle, const Vector3& rotationAxis) const
{
    const int segments = 360;
    const float angleStep = 2 * PI / segments;

    auto RotatePoint = [](const Vector3& point, float angleDeg, const Vector3& axis, const Vector3& center) -> Vector3 {
        float rad = angleDeg * (PI / 180.0f);
        float cosA = cos(rad);
        float sinA = sin(rad);

        Vector3 normalizedAxis = axis;
        float length = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
        if (length > 0) {
            normalizedAxis.x = axis.x / length;
            normalizedAxis.y = axis.y / length;
            normalizedAxis.z = axis.z / length;
        }

        float x = normalizedAxis.x;
        float y = normalizedAxis.y;
        float z = normalizedAxis.z;

        Vector3 translated = {
            point.x - center.x,
            point.y - center.y,
            point.z - center.z
        };

        float oneMinusCos = 1.0f - cosA;

        float rotatedX = translated.x * (cosA + x * x * oneMinusCos) +
            translated.y * (x * y * oneMinusCos - z * sinA) +
            translated.z * (x * z * oneMinusCos + y * sinA);

        float rotatedY = translated.x * (y * x * oneMinusCos + z * sinA) +
            translated.y * (cosA + y * y * oneMinusCos) +
            translated.z * (y * z * oneMinusCos - x * sinA);

        float rotatedZ = translated.x * (z * x * oneMinusCos - y * sinA) +
            translated.y * (z * y * oneMinusCos + x * sinA) +
            translated.z * (cosA + z * z * oneMinusCos);

        return {
            rotatedX + center.x,
            rotatedY + center.y,
            rotatedZ + center.z
        };
        };

    for (int i = 0; i < segments; i++) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        Vector3 v1 = { position.x + (float)(radius * cos(angle1)),
                       position.y + (float)(radius * sin(angle1)),
                       position.z };
        Vector3 v2 = { position.x + (float)(radius * cos(angle2)),
                       position.y + (float)(radius * sin(angle2)),
                       position.z };
        
        v1 = RotatePoint(v1, rotationAngle, rotationAxis, position);
        v2 = RotatePoint(v2, rotationAngle, rotationAxis, position);

        DrawLine3D(v1, v2, BLUE);
    }

    Point3D current = GetPoint(t);
    Vector3 pointPos = { position.x + current.x, position.y + current.y, position.z + current.z };
    pointPos = RotatePoint(pointPos, rotationAngle, rotationAxis, position);

    DrawSphere(pointPos, 0.1f, RED);

    Vector3D derivative = GetDerivative(t);
    Vector3 endPoint = { pointPos.x + derivative.x * 0.3f,
                         pointPos.y + derivative.y * 0.3f,
                         pointPos.z + derivative.z * 0.3f };
    endPoint = RotatePoint(endPoint, rotationAngle, rotationAxis, position);

    DrawLine3D(pointPos, endPoint, BLACK);
}