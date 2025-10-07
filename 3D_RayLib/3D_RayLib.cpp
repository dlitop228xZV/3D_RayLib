#include <raylib.h>
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include "RandomCreate.h"

int main()
{
    InitWindow(1280, 960, "3D Project");

    Circle circle(2);
    Ellipse ellipse(3, 1.5);
    Helixes helixes(1, 0.5);
    double t = 0;
    int turns = 1;  // для нормальной отрисовки шара у Helixes

    RandomCreate RC;
    int index = 0;
    const int numCurve = 10;

    enum DRAW {ALL,ONLY_CIRCLE};
    int currentDraw = 0;

    std::vector<Curve*> curves = RC.createRandomCurves(numCurve);
    std::vector<Circle*> circlesOnly;

    for (int i = 0; i < curves.size(); ++i)
    {
        Circle* circle = dynamic_cast<Circle*>(curves[i]);
        if (circle)
        {
            circlesOnly.push_back(circle);
        }
    }

    for (int i = 0; i < circlesOnly.size() - 1; ++i)
    {
        for (int j = 0; j < circlesOnly.size() - i - 1; ++j)
        {
            if (circlesOnly[j]->GetRadius() > circlesOnly[j + 1]->GetRadius())
            {
                Circle* temp = circlesOnly[j];
                circlesOnly[j] = circlesOnly[j + 1];
                circlesOnly[j + 1] = temp;
            }
        }
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

        if (IsKeyPressed(KEY_ONE))
        {
            index = 0;
            currentDraw = ALL;
        }
        if (IsKeyPressed(KEY_TWO))
        {
            index = 0;
            currentDraw = ONLY_CIRCLE;
        }

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

        switch (currentDraw)
        {
        case ALL:
            curves[index]->Draw(t, { 0, 0, 0 });
            if (dynamic_cast<Helixes*>(curves[index]))
                turns = 2;
            else
                turns = 1;
            break;
        case ONLY_CIRCLE:
            if(!circlesOnly.empty() && index < circlesOnly.size())
                circlesOnly[index]->Draw(t, { 0, 0, 0 });
            if (index > circlesOnly.size()-1)
                index = 0;
        default:
            break;
        }
        

        EndMode3D();

        DrawRectangle(10, 10, 320, 193, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 320, 193, BLUE);

        DrawText("Free camera default controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
        DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
        DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
        DrawText("LEFT - RIGHT", 20, 100, 10, BLACK);
        DrawText(TextFormat("- Index: %d", index), 40, 120, 10, DARKGRAY);

        if(currentDraw == ALL)
        {
            Vector3 p = curves[index]->GetPoint(t);
            DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 140, 10, DARKGRAY);
            Vector3 d = curves[index]->GetDerivative(t);
            DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 160, 10, DARKGRAY);
            DrawText(TextFormat("- Radius: %.2f", curves[index]->GetRadius()), 40, 180, 10, DARKGRAY);
        }
        else if(currentDraw == ONLY_CIRCLE && !circlesOnly.empty() && index < circlesOnly.size())
            {
                Vector3 p = circlesOnly[index]->GetPoint(t);
                DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 140, 10, DARKGRAY);
                Vector3 d = circlesOnly[index]->GetDerivative(t);
                DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 160, 10, DARKGRAY);
                DrawText(TextFormat("- Radius: %.2f", circlesOnly[index]->GetRadius()), 40, 180, 10, DARKGRAY);
            }

        EndDrawing();
    }

    RC.deletedCurve(curves);
    circlesOnly.clear();

    CloseWindow();

    return 0;
}