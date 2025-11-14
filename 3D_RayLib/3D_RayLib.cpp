#define RAYGUI_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include <raylib.h>
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include "RandomCreate.h"
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include "UI.h"

int main()
{
    InitWindow(1280, 960, "3D Project - Curve Editor");
    SetExitKey(KEY_NULL);

    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    bool cameraControl = true;

    UI ui;

    double t = PI / 4;
    int turns = 1;
    int index = 0;
    const int numCurve = 10;

    enum DRAW { ALL, ONLY_CIRCLE, CUSTOM };
    int currentDraw = ALL;

    // Создаем случайные фигуры по умолчанию
    RandomCreate RC;
    std::vector<std::shared_ptr<Curve>> curves = RC.createRandomCurves(numCurve);
    std::vector<std::shared_ptr<Circle>> circlesOnly;

    for (auto& curve : curves)
    {
        if (auto circle = std::dynamic_pointer_cast<Circle>(curve))
            circlesOnly.push_back(circle);
    }

    std::sort(circlesOnly.begin(), circlesOnly.end(),
        [](const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
            return a->GetRadius() < b->GetRadius();
        });

    double totalRadius = 0;
    for (const auto& circle : circlesOnly)
        totalRadius += circle->GetRadius();

    // Печать значений в консоль (требование 3)
    std::cout << "\n\nRandom Curves:\n";
    for (size_t i = 0; i < curves.size(); ++i)
    {
        Vector3 p = curves[i]->GetPoint(PI / 4);
        Vector3 d = curves[i]->GetDerivative(PI / 4);
        std::cout << "Curve #" << i << ":\n";
        std::cout << "  Point: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
        std::cout << "  Derivative: (" << d.x << ", " << d.y << ", " << d.z << ")\n";
    }
    std::cout << "\n\n";

    Camera3D camera = { 0 };
    camera.position = Vector3{ 10.0f, 10.0f, 10.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    bool cursorEnabled = true;

    EnableCursor();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        t += 0.01;
        if (t > turns * 2 * PI)
            t -= turns * 2 * PI;

        if (!ui.IsUIOpen()) {
            if (IsKeyPressed(KEY_ONE)) { index = 0; currentDraw = ALL; }
            if (IsKeyPressed(KEY_TWO)) { index = 0; currentDraw = ONLY_CIRCLE; }
            if (IsKeyPressed(KEY_THREE)) { index = 0; currentDraw = CUSTOM; }
        }

        if (ui.IsUIOpen()) {
            if (!cursorEnabled) {
                EnableCursor();
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
                cursorEnabled = true;
            }
        }
        else {
            if (cursorEnabled) {
                DisableCursor();
                cursorEnabled = false;
            }
            UpdateCamera(&camera, CAMERA_FREE);
        }


        if (IsKeyPressed('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };

        // Навигация по фигурам
        if (IsKeyPressed(KEY_LEFT)) {
            switch (currentDraw) {
            case ALL:
                if (!curves.empty())
                    index = (index - 1 + curves.size()) % curves.size();
                break;
            case ONLY_CIRCLE:
                if (!circlesOnly.empty())
                    index = (index - 1 + circlesOnly.size()) % circlesOnly.size();
                break;
            case CUSTOM:
                if (!ui.customCurves.empty())
                    index = (index - 1 + ui.customCurves.size()) % ui.customCurves.size();
                break;
            }
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            switch (currentDraw) {
            case ALL:
                if (!curves.empty())
                    index = (index + 1) % curves.size();
                break;
            case ONLY_CIRCLE:
                if (!circlesOnly.empty())
                    index = (index + 1) % circlesOnly.size();
                break;
            case CUSTOM:
                if (!ui.customCurves.empty())
                    index = (index + 1) % ui.customCurves.size();
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);


        BeginMode3D(camera);

        DrawGrid(10, 1.0f);

        // Позиция и ориентация из UI
        Point3D customPosition = ui.GetCurrentPosition();
        Vector3D customDirection = ui.GetCurrentDirection();
        float customTilt = ui.GetCurrentTilt();

        switch (currentDraw)
        {
        case ALL:
            if (index < curves.size()) {
                curves[index]->Draw(t, { 0, 0, 0 }, ui.GetCurrentTilt(), ui.GetCurrentRotationAxis());
                turns = (std::dynamic_pointer_cast<Helixes>(curves[index])) ? 2 : 1;
            }
            break;
        case ONLY_CIRCLE:
            if (!circlesOnly.empty() && index < circlesOnly.size()) {
                circlesOnly[index]->Draw(t, { 0, 0, 0 }, ui.GetCurrentTilt(), ui.GetCurrentRotationAxis());
            }
            break;
        case CUSTOM:
            if (!ui.customCurves.empty() && index < ui.customCurves.size()) {
                ui.customCurves[index]->Draw(t, customPosition, ui.GetCurrentTilt(), ui.GetCurrentRotationAxis());
                turns = (std::dynamic_pointer_cast<Helixes>(ui.customCurves[index])) ? 2 : 1;
            }
            break;
        default:
            break;
        }

        EndMode3D();

        // Информационная панель
        DrawRectangle(10, 10, 350, 280, Fade(SKYBLUE, 0.5f));
        DrawRectangleLines(10, 10, 350, 280, BLUE);

        DrawText("Camera Controls:", 20, 20, 10, BLACK);
        DrawText("- Mouse to look around", 40, 40, 10, DARKGRAY);
        DrawText("- WASD to move", 40, 60, 10, DARKGRAY);
        DrawText("- Q/E to move up/down", 40, 80, 10, DARKGRAY);
        DrawText("- Z to reset view", 40, 100, 10, DARKGRAY);

        DrawText("Navigation:", 20, 120, 10, BLACK);
        DrawText("1=ALL, 2=CIRCLES, 3=CUSTOM", 40, 140, 10, DARKGRAY);
        DrawText("LEFT/RIGHT - switch curves", 40, 160, 10, DARKGRAY);

        DrawText(TextFormat("- Index: %d", index), 40, 180, 10, DARKGRAY);
        DrawText(TextFormat("- Mode: %s",
            currentDraw == ALL ? "ALL" :
            currentDraw == ONLY_CIRCLE ? "CIRCLES" : "CUSTOM"),
            40, 200, 10, DARKGRAY);

        // Отображение информации о текущей фигуре
        if (currentDraw == ALL && index < curves.size())
        {
            Vector3 p = curves[index]->GetPoint(t);
            Vector3 d = curves[index]->GetDerivative(t);
            DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 220, 10, DARKGRAY);
            DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 240, 10, DARKGRAY);
            DrawText(TextFormat("- Radius: %.2f", curves[index]->GetRadius()), 40, 260, 10, DARKGRAY);
        }
        else if (currentDraw == ONLY_CIRCLE && index < circlesOnly.size())
        {
            Vector3 p = circlesOnly[index]->GetPoint(t);
            Vector3 d = circlesOnly[index]->GetDerivative(t);
            DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 220, 10, DARKGRAY);
            DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 240, 10, DARKGRAY);
            DrawText(TextFormat("- Radius: %.2f", circlesOnly[index]->GetRadius()), 40, 260, 10, DARKGRAY);
        }
        else if (currentDraw == CUSTOM && index < ui.customCurves.size())
        {
            Vector3 p = ui.customCurves[index]->GetPoint(t);
            Vector3 d = ui.customCurves[index]->GetDerivative(t);
            DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 220, 10, DARKGRAY);
            DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 240, 10, DARKGRAY);
            DrawText(TextFormat("- Radius: %.2f", ui.customCurves[index]->GetRadius()), 40, 260, 10, DARKGRAY);
        }

        DrawText("Press 'O' to open/close curve editor", 10, GetScreenHeight() - 30, 20, DARKGRAY);

        ui.Show();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}