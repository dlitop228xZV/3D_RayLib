#include <raylib.h>
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include "RandomCreate.h"

#include <iostream>

int main()
{
    setlocale(LC_ALL, "RUS");

    InitWindow(1280, 960, "3D Project");

    Circle circle(2);
    Ellipse ellipse(3, 1.5);
    Helixes helixes(1, 0.5);
    double t = 0;
    int turns = 1;  // для нормальной отрисовки шара у Helixes

    RandomCreate RC;
    int index = 0;
    const int numCurve = 10;
    std::vector<Curve*> curves = RC.createRandomCurves(numCurve);


    if (curves.empty()) {
        std::cerr << "\n\tВектор пуст\n\n";
        return 404;
    }
    else {
        std::cerr << "\n\tВектор не пуст\n\n";
        std::cerr << curves.size() << '\n';
    }


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
        if (t > turns * 2 * PI)
            t -= turns * 2 * PI;

        UpdateCamera(&camera, CAMERA_FREE); 

        if (IsKeyPressed('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };

        if (IsKeyPressed(KEY_LEFT))
        {
            index--;
            if (index < 0)
                index = numCurve - 1;
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            index++;
            if (index > numCurve - 1)
                index = 0;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        if (!curves.empty() && index >= 0 && index < (int)curves.size())
        {
            curves[index]->Draw(t, { 0, 0, 0 });
            if (dynamic_cast<Helixes*>(curves[index]))
                turns = 2;
            else
                turns = 1;
        }

        EndMode3D();

        DrawRectangle(10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 320, 133, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
        DrawText("LEFT - RIGHT", 20, 100, 10, BLACK);
        DrawText(TextFormat("- Index: %d", index), 40, 120, 10, DARKGRAY);


        EndDrawing();
    }


    CloseWindow();

    return 0;
}