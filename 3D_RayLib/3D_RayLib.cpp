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

int main()
{
	InitWindow(1280, 960, "3D Project");

	double t = PI / 4;
	int turns = 1;
	double totalRadius = 0;
	RandomCreate RC;
	int index = 0;
	const int numCurve = 10;

	enum DRAW { ALL, ONLY_CIRCLE };
	int currentDraw = 0;

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

	for (const auto& circle : circlesOnly)
		totalRadius += circle->GetRadius();

	// Печать значений в консоль (требование 3)
	std::cout << "\n\n";
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

	DisableCursor();
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		t += 0.01;
		if (t > turns * 2 * PI)
			t -= turns * 2 * PI;

		if (IsKeyPressed(KEY_ONE)) { index = 0; currentDraw = ALL; }
		if (IsKeyPressed(KEY_TWO)) { index = 0; currentDraw = ONLY_CIRCLE; }

		UpdateCamera(&camera, CAMERA_FREE);
		if (IsKeyPressed('Z')) camera.target = Vector3{ 0.0f, 0.0f, 0.0f };

		if (IsKeyPressed(KEY_LEFT)) index = (index - 1 + numCurve) % numCurve;
		if (IsKeyPressed(KEY_RIGHT)) index = (index + 1) % numCurve;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode3D(camera);

		DrawGrid(10, 1.0f);

		switch (currentDraw)
		{
		case ALL:
			curves[index]->Draw(t, { 0, 0, 0 });
			turns = (std::dynamic_pointer_cast<Helixes>(curves[index])) ? 2 : 1;
			break;
		case ONLY_CIRCLE:
			if (!circlesOnly.empty() && index < circlesOnly.size())
				circlesOnly[index]->Draw(t, { 0, 0, 0 });
			if (index >= circlesOnly.size()) index = 0;
			break;
		default:
			break;
		}

		EndMode3D();

		DrawRectangle(10, 10, 320, 223, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 320, 223, BLUE);

		DrawText("Free camera default controls:", 20, 20, 10, BLACK);
		DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
		DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);
		DrawText("LEFT - RIGHT | 1 = ALL , 2 = only circles", 20, 100, 10, BLACK);
		DrawText(TextFormat("- Index: %d", index), 40, 120, 10, DARKGRAY);

		if (currentDraw == ALL && index < curves.size())
		{
			Vector3 p = curves[index]->GetPoint(t);
			Vector3 d = curves[index]->GetDerivative(t);
			DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 140, 10, DARKGRAY);
			DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 160, 10, DARKGRAY);
			DrawText(TextFormat("- Radius: %.2f", curves[index]->GetRadius()), 40, 180, 10, DARKGRAY);
		}
		else if (currentDraw == ONLY_CIRCLE && index < circlesOnly.size())
		{
			Vector3 p = circlesOnly[index]->GetPoint(t);
			Vector3 d = circlesOnly[index]->GetDerivative(t);
			DrawText(TextFormat("- Point: (%.2f, %.2f, %.2f)", p.x, p.y, p.z), 40, 140, 10, DARKGRAY);
			DrawText(TextFormat("- Derivative: (%.2f, %.2f, %.2f)", d.x, d.y, d.z), 40, 160, 10, DARKGRAY);
			DrawText(TextFormat("- Radius: %.2f", circlesOnly[index]->GetRadius()), 40, 180, 10, DARKGRAY);
			DrawText(TextFormat("- totalRadius: %.2f", totalRadius), 40, 200, 10, DARKGRAY);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
