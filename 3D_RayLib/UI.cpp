#include "UI.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include <iostream>
#include <algorithm>
#include <string>

void UI::Draw()
{
    DrawRectangleRec(main, LIGHTGRAY);
    DrawRectangleLinesEx(main, 1, BLACK);

    // Панель создания фигур
    DrawCurveCreationPanel();

    // Панель позиции и ориентации
    DrawPositionPanel();

    // Список фигур
    DrawCurveListPanel();
}

void UI::DrawCurveCreationPanel()
{
    Rectangle panel = { main.x + 20, main.y + 20, main.width - 40, 200 };
    DrawRectangleRec(panel, Fade(WHITE, 0.8f));
    DrawRectangleLinesEx(panel, 1, DARKGRAY);

    DrawText("Create New Curve", panel.x + 10, panel.y + 10, 20, BLACK);

    GuiLabel({ panel.x + 10, panel.y + 40, 100, 25 }, "Curve Type:");

    if (GuiButton({ panel.x + 120, panel.y + 40, 80, 25 }, "Circle")) {
        selectedCurveType = 0;
    }
    if (GuiButton({ panel.x + 210, panel.y + 40, 80, 25 }, "Ellipse")) {
        selectedCurveType = 1;
    }
    if (GuiButton({ panel.x + 300, panel.y + 40, 80, 25 }, "Helix")) {
        selectedCurveType = 2;
    }

    const char* curveTypes[] = { "Circle", "Ellipse", "Helix" };
    DrawText(TextFormat("Selected: %s", curveTypes[selectedCurveType]), panel.x + 400, panel.y + 45, 16, DARKGRAY);

    // поля ввода
    switch (selectedCurveType) {
    case 0:
        GuiLabel({ panel.x + 10, panel.y + 75, 100, 25 }, "Radius:");
        if (GuiTextBox({ panel.x + 120, panel.y + 75, 150, 25 },
            radiusInputText, 32, editRadius))
        {
            editRadius = !editRadius;
        }
        radiusInput = atof(radiusInputText);
        break;

    case 1:
        GuiLabel({ panel.x + 10, panel.y + 75, 100, 25 }, "Radius X:");
        if (GuiTextBox({ panel.x + 120, panel.y + 75, 150, 25 },
            radiusXInputText, 32, editRadiusX))
        {
            editRadiusX = !editRadiusX;
        }
        radiusXInput = atof(radiusXInputText);

        GuiLabel({ panel.x + 10, panel.y + 110, 100, 25 }, "Radius Y:");
        if (GuiTextBox({ panel.x + 120, panel.y + 110, 150, 25 },
            radiusYInputText, 32, editRadiusY))
        {
            editRadiusY = !editRadiusY;
        }
        radiusYInput = atof(radiusYInputText);
        break;

    case 2:
        GuiLabel({ panel.x + 10, panel.y + 75, 100, 25 }, "Radius:");
        if (GuiTextBox({ panel.x + 120, panel.y + 75, 150, 25 },
            radiusInputText, 32, editRadius))
        {
            editRadius = !editRadius;
        }
        radiusInput = atof(radiusInputText);

        GuiLabel({ panel.x + 10, panel.y + 110, 100, 25 }, "Step:");
        if (GuiTextBox({ panel.x + 120, panel.y + 110, 150, 25 },
            stepInputText, 32, editStep))
        {
            editStep = !editStep;
        }
        stepInput = atof(stepInputText);
        break;
    }

    if (GuiButton({ panel.x + 10, panel.y + 150, 120, 30 }, "Create Curve")) {
        std::shared_ptr<Curve> newCurve = nullptr;
        if (selectedCurveType == 0 && radiusInput > 0)
            newCurve = std::make_shared<Circle>(radiusInput);
        else if (selectedCurveType == 1 && radiusXInput > 0 && radiusYInput > 0)
            newCurve = std::make_shared<Ellipse>(radiusXInput, radiusYInput);
        else if (selectedCurveType == 2 && radiusInput > 0)
            newCurve = std::make_shared<Helixes>(radiusInput, stepInput);

        if (newCurve)
            AddCurve(newCurve);
    }
}


void UI::DrawPositionPanel()
{
    Rectangle panel = { main.x + 20, main.y + 240, main.width - 40, 240 };
    DrawRectangleRec(panel, WHITE);
    DrawRectangleLinesEx(panel, 1, DARKGRAY);

    DrawText("Position & Orientation", panel.x + 10, panel.y + 10, 20, BLACK);

    // --- Позиция ---
    GuiLabel({ panel.x + 10, panel.y + 40, 80, 25 }, "Position X:");
    if (GuiTextBox({ panel.x + 100, panel.y + 40, 80, 25 }, posXInputText, 32, editPosX))
        editPosX = !editPosX;
    posXInput = atof(posXInputText);

    GuiLabel({ panel.x + 190, panel.y + 40, 80, 25 }, "Y:");
    if (GuiTextBox({ panel.x + 220, panel.y + 40, 80, 25 }, posYInputText, 32, editPosY))
        editPosY = !editPosY;
    posYInput = atof(posYInputText);

    GuiLabel({ panel.x + 310, panel.y + 40, 80, 25 }, "Z:");
    if (GuiTextBox({ panel.x + 340, panel.y + 40, 80, 25 }, posZInputText, 32, editPosZ))
        editPosZ = !editPosZ;
    posZInput = atof(posZInputText);

    // --- Ротация ---
    GuiLabel({ panel.x + 10, panel.y + 75, 100, 25 }, "Rotation Axis X:");
    if (GuiTextBox({ panel.x + 120, panel.y + 75, 80, 25 }, rotationXInputText, 32, editRotationX))
        editRotationX = !editRotationX;
    rotationXInput = atof(rotationXInputText);

    GuiLabel({ panel.x + 210, panel.y + 75, 80, 25 }, "Y:");
    if (GuiTextBox({ panel.x + 230, panel.y + 75, 80, 25 }, rotationYInputText, 32, editRotationY))
        editRotationY = !editRotationY;
    rotationYInput = atof(rotationYInputText);

    GuiLabel({ panel.x + 320, panel.y + 75, 80, 25 }, "Z:");
    if (GuiTextBox({ panel.x + 340, panel.y + 75, 80, 25 }, rotationZInputText, 32, editRotationZ))
        editRotationZ = !editRotationZ;
    rotationZInput = atof(rotationZInputText);

    // --- Угол ротации ---
    GuiLabel({ panel.x + 10, panel.y + 110, 100, 25 }, "Rotation Angle:");
    if (GuiTextBox({ panel.x + 120, panel.y + 110, 80, 25 }, rotationAngleInputText, 32, editRotationAngle))
        editRotationAngle = !editRotationAngle;
    rotationAngleInput = atof(rotationAngleInputText);

    // --- Кнопки XYZ Ротации ---
    if (GuiButton({ panel.x + 220, panel.y + 110, 80, 25 }, "X-Axis")) {
        rotationXInput = 1.0f; rotationYInput = 0.0f; rotationZInput = 0.0f;
        snprintf(rotationXInputText, sizeof(rotationXInputText), "1.0");
        snprintf(rotationYInputText, sizeof(rotationYInputText), "0.0");
        snprintf(rotationZInputText, sizeof(rotationZInputText), "0.0");
    }
    if (GuiButton({ panel.x + 310, panel.y + 110, 80, 25 }, "Y-Axis")) {
        rotationXInput = 0.0f; rotationYInput = 1.0f; rotationZInput = 0.0f;
        snprintf(rotationXInputText, sizeof(rotationXInputText), "0.0");
        snprintf(rotationYInputText, sizeof(rotationYInputText), "1.0");
        snprintf(rotationZInputText, sizeof(rotationZInputText), "0.0");
    }
    if (GuiButton({ panel.x + 400, panel.y + 110, 80, 25 }, "Z-Axis")) {
        rotationXInput = 0.0f; rotationYInput = 0.0f; rotationZInput = 1.0f;
        snprintf(rotationXInputText, sizeof(rotationXInputText), "0.0");
        snprintf(rotationYInputText, sizeof(rotationYInputText), "0.0");
        snprintf(rotationZInputText, sizeof(rotationZInputText), "1.0");
    }

    if (GuiButton({ panel.x + 10, panel.y + 145, 120, 25 }, "Reset All")) {
        // Сброс позиции
        posXInput = 0.0f; posYInput = 0.0f; posZInput = 0.0f;
        snprintf(posXInputText, sizeof(posXInputText), "0.0");
        snprintf(posYInputText, sizeof(posYInputText), "0.0");
        snprintf(posZInputText, sizeof(posZInputText), "0.0");

        // Сброс поворота 
        rotationXInput = 0.0f; rotationYInput = 1.0f; rotationZInput = 0.0f;
        rotationAngleInput = 0.0f;
        snprintf(rotationXInputText, sizeof(rotationXInputText), "0.0");
        snprintf(rotationYInputText, sizeof(rotationYInputText), "1.0");
        snprintf(rotationZInputText, sizeof(rotationZInputText), "0.0");
        snprintf(rotationAngleInputText, sizeof(rotationAngleInputText), "0.0");
    }
}



void UI::DrawCurveListPanel()
{
    Rectangle panel = { main.x + 20, main.y + 440, main.width - 40, main.height - 460 };
    DrawRectangleRec(panel, Fade(WHITE, 0.8f));
    DrawRectangleLinesEx(panel, 1, DARKGRAY);

    DrawText("Curves List", panel.x + 10, panel.y + 10, 20, BLACK);
    DrawText(TextFormat("Total Curves: %d", (int)customCurves.size()), panel.x + 10, panel.y + 40, 16, DARKGRAY);
    DrawText(TextFormat("Total Circles Radius: %.2f", totalRadius), panel.x + 10, panel.y + 60, 16, DARKGRAY);

    // Список фигур
    Rectangle listRect = { panel.x + 10, panel.y + 90, panel.width - 20, panel.height - 130 };
    DrawRectangleRec(listRect, Fade(LIGHTGRAY, 0.5f));
    DrawRectangleLinesEx(listRect, 1, GRAY);

    float yPos = listRect.y + 10;
    for (size_t i = 0; i < customCurves.size(); i++) {
        std::string curveInfo;
        if (std::dynamic_pointer_cast<Circle>(customCurves[i])) {
            auto circle = std::dynamic_pointer_cast<Circle>(customCurves[i]);
            curveInfo = TextFormat("Circle %d - Radius: %.2f", (int)i + 1, circle->GetRadius());
        }
        else if (std::dynamic_pointer_cast<Ellipse>(customCurves[i])) {
            auto ellipse = std::dynamic_pointer_cast<Ellipse>(customCurves[i]);
            curveInfo = TextFormat("Ellipse %d - Radius: %.2f", (int)i + 1, ellipse->GetRadius());
        }
        else if (std::dynamic_pointer_cast<Helixes>(customCurves[i])) {
            auto helix = std::dynamic_pointer_cast<Helixes>(customCurves[i]);
            curveInfo = TextFormat("Helix %d - Radius: %.2f, Step: %.2f", (int)i + 1, helix->GetRadius(), stepInput);
        }
        else {
            curveInfo = TextFormat("Unknown Curve %d", (int)i + 1);
        }

        // Отображение инфо о фигуре
        DrawText(curveInfo.c_str(), listRect.x + 10, yPos, 16, BLACK);

        if (GuiButton({ listRect.x + listRect.width - 100, yPos, 80, 25 }, "Delete")) {
            RemoveCurve((int)i);
            break;
        }

        yPos += 35;
    }

    if (GuiButton({ panel.x + 10, panel.y + panel.height - 30, 120, 25 }, "Clear All")) {
        customCurves.clear();
        customCircles.clear();
        totalRadius = 0;
        selectedCurveIndex = 0;
    }
}

void UI::Update()
{
    if (IsKeyPressed(KEY_O))
    {
        main.x = GetScreenWidth() / 2 - size / 2;
        main.y = GetScreenHeight() / 2 - size / 2;
        IsOpen = !IsOpen;
    }
}

void UI::Show()
{
    Update();
    if (IsOpen)
        Draw();
}



void UI::AddCurve(std::shared_ptr<Curve> curve)
{
    if (curve) {
        customCurves.push_back(curve);

        if (auto circle = std::dynamic_pointer_cast<Circle>(curve)) {
            customCircles.push_back(circle);
            UpdateCirclesList();
        }
    }
}

void UI::RemoveCurve(int index)
{
    if (index >= 0 && index < (int)customCurves.size()) {
        if (auto circle = std::dynamic_pointer_cast<Circle>(customCurves[index])) {
            auto it = std::find(customCircles.begin(), customCircles.end(), circle);
            if (it != customCircles.end()) {
                customCircles.erase(it);
            }
        }

        customCurves.erase(customCurves.begin() + index);
        UpdateCirclesList();

        if (selectedCurveIndex >= (int)customCurves.size()) {
            selectedCurveIndex = std::max(0, (int)customCurves.size() - 1);
        }
    }
}

void UI::UpdateCirclesList()
{
    std::sort(customCircles.begin(), customCircles.end(),
        [](const std::shared_ptr<Circle>& a, const std::shared_ptr<Circle>& b) {
            return a->GetRadius() < b->GetRadius();
        });

    totalRadius = 0;
    for (const auto& circle : customCircles) {
        totalRadius += circle->GetRadius();
    }
}

Point3D UI::GetCurrentPosition() const
{
    return Point3D{ posXInput, posYInput, posZInput };
}

Vector3D UI::GetCurrentDirection() const
{
    return Vector3D{ dirXInput, dirYInput, dirZInput };
}

float UI::GetCurrentTilt() const
{
    return rotationAngleInput;
}

Vector3D UI::GetCurrentRotationAxis() const
{
    return Vector3D{ rotationXInput, rotationYInput, rotationZInput };
}