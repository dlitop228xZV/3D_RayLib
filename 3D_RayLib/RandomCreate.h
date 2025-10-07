#pragma once
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include <raylib.h>
#include <vector>

class RandomCreate
{
private:
	const double min = 1;
	const double max = 5;
	double random();
public:

	Curve* createRandomCurve();

	Circle* createRandomCircle();
	Ellipse* createRandomEllipse();
	Helixes* createRandomHelix();

	std::vector<Curve*> createRandomCurves(int count);

	void deletedCurve(std::vector<Curve*>& curves);
};

