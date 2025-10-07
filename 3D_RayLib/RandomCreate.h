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
	const double min = 0.5;
	const double max = 5;
	double random();
public:

	Curve* createRandomCurve();

	Circle* createRandomCircle();
	Ellipse* createRandomEllipse();
	Helixes* createRandomHelix();


	std::vector<Curve*> createRandomCurves(int count);
	std::vector<Circle*> createRandomCircles(int count);
	std::vector<Ellipse*> createRandomEllipses(int count);
	std::vector<Helixes*> createRandomHelixes(int count);

	void deletedCurve(std::vector<Curve*>& curves);
	void deletedEllipse(std::vector<Ellipse*>& ellipses);
	void deletedHelixes(std::vector<Helixes*>& helixes);
};

