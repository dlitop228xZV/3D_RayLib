#include "RandomCreate.h"


double RandomCreate::random()
{
	double r = GetRandomValue(min, max);
	return r;
}

Curve* RandomCreate::createRandomCurve()
{
	int Rcurve = GetRandomValue(0, 3);

	switch (Rcurve)
	{
	case 0:
		createRandomCircle();
		break;
	case 1:
		createRandomEllipse();
		break;
	case 2:
		createRandomHelix();
		break;
	default:
		break;
	}

	return 0;
}

Circle* RandomCreate::createRandomCircle()
{
	return new Circle(random());
}

Ellipse* RandomCreate::createRandomEllipse()
{
	return new Ellipse(random(), random());
}

Helixes* RandomCreate::createRandomHelix()
{
	return new Helixes(random(), random());
}

std::vector<Curve*> RandomCreate::createRandomCurves(int count)
{
	std::vector<Curve*> curves;

	for (int i = 0; i <= count; i++)
	{
		curves.push_back(createRandomCurve());
	}
	return curves;
}

std::vector<Circle*> RandomCreate::createRandomCircles(int count)
{
	std::vector<Circle*> circles;

	for (int i = 0; i <= count; i++)
	{
		circles.push_back(createRandomCircle());
	}
	return circles;
}

std::vector<Ellipse*> RandomCreate::createRandomEllipses(int count)
{
	std::vector<Ellipse*> ellipses;

	for (int i = 0; i <= count; i++)
	{
		ellipses.push_back(createRandomEllipse());
	}
	return ellipses;
}

std::vector<Helixes*> RandomCreate::createRandomHelixes(int count)
{
	std::vector<Helixes*> xelises;

	for (int i = 0; i <= count; i++)
	{
		xelises.push_back(createRandomHelix());
	}
	return xelises;
}

void RandomCreate::deletedCurve(std::vector<Curve*>& curves)
{
	curves.clear();
}

void RandomCreate::deletedEllipse(std::vector<Ellipse*>& ellipses)
{
	ellipses.clear();
}

void RandomCreate::deletedHelixes(std::vector<Helixes*>& helixes)
{
	helixes.clear();
}
