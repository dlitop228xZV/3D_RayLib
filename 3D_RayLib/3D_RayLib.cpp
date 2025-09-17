#include <raylib.h>
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"

int main()
{
    InitWindow(1280, 960, "3D Project");

    Circle circle(2);
    Ellipse ellipse(3, 1.5);
    Helixes helixes(3, 1.5);
    double t = 0;

    Camera3D camera = { 0 };
    camera.position = Vector3{ 10.0f, 10.0f, 10.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        t += 0.01;
        if (t > 2 * PI)
            t -= 2 * PI;

        UpdateCamera(&camera, CAMERA_FREE);

        if (IsKeyPressed('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        circle.Draw(t, { -3,0,0 });
        ellipse.Draw(t, { 3,0,0 });
        helixes.Draw(t, { 0,3,0 });

        EndMode3D();

        DrawRectangle(10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 320, 93, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}