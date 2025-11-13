#pragma once

#include <raylib.h>
#include <raygui.h>
#include <vector>
#include <memory>
#include <string>
#include "Curve.h"

class Circle;
class Ellipse;
class Helixes;

class UI
{
private:

    bool editRadius = false;
    bool editRadiusX = false;
    bool editRadiusY = false;
    bool editStep = false;

    bool editPosX = false;
    bool editPosY = false;
    bool editPosZ = false;
    bool editDirX = false;
    bool editDirY = false;
    bool editDirZ = false;
    bool editTilt = false;


    float size = 800;
    Rectangle main = { 0,0,size,size };
    bool IsOpen = false;

    // UI элементы для создания фигур
    int selectedCurveType = 0; // 0: Circle, 1: Ellipse, 2: Helix
    float radiusInput = 1.0f;
    float radiusXInput = 1.0f;
    float radiusYInput = 1.0f;
    float stepInput = 0.5f;
    int selectedCurveIndex = 0;

    // Поля для позиции, направления и наклона
    float posXInput = 0.0f;
    float posYInput = 0.0f;
    float posZInput = 0.0f;
    float dirXInput = 0.0f;
    float dirYInput = 0.0f;
    float dirZInput = 1.0f;
    float tiltInput = 0.0f;

    char radiusInputText[32] = "1.0";
    char radiusXInputText[32] = "1.0";
    char radiusYInputText[32] = "1.0";
    char stepInputText[32] = "0.5";
    char posXInputText[32] = "0.0";
    char posYInputText[32] = "0.0";
    char posZInputText[32] = "0.0";
    char dirXInputText[32] = "0.0";
    char dirYInputText[32] = "0.0";
    char dirZInputText[32] = "1.0";
    char tiltInputText[32] = "0.0";

    void Draw();
    void Update();
    void DrawCurveCreationPanel();
    void DrawCurveListPanel();
    void DrawPositionPanel();

public:
    UI();

    std::vector<std::shared_ptr<Curve>> customCurves;
    std::vector<std::shared_ptr<Circle>> customCircles;
    double totalRadius = 0;

    void Show();
    void AddCurve(std::shared_ptr<Curve> curve);
    void RemoveCurve(int index);
    void UpdateCirclesList();

    Point3D GetCurrentPosition() const;
    Vector3D GetCurrentDirection() const;
    float GetCurrentTilt() const;
    bool IsUIOpen() const { return IsOpen; }

};