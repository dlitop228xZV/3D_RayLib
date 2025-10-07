#pragma once
#include "Curve.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Helixes.h"
#include <raylib.h>
#include <memory>
#include <vector>

class RandomCreate
{
private:
	const double min = 1;
	const double max = 5;
	double random();
public:

	std::shared_ptr<Curve> createRandomCurve();

	std::shared_ptr<Circle> createRandomCircle();
	std::shared_ptr<Ellipse> createRandomEllipse();
	std::shared_ptr<Helixes> createRandomHelix();

	std::vector<std::shared_ptr<Curve>> createRandomCurves(int count);
};

