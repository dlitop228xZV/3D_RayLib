#include "RandomCreate.h"


double RandomCreate::random()
{
	//double r = GetRandomValue(min, max);
	double r = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5 - 1)));
	return r;
}

Curve* RandomCreate::createRandomCurve()
{
	int Rcurve = GetRandomValue(0, 2);

	switch (Rcurve)
	{
	case 0:
		return createRandomCircle();
	case 1:
		return createRandomEllipse();
	case 2:
		return createRandomHelix();
	default:
		return nullptr;
	}
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

	for (int i = 0; i < count; i++)
	{
		Curve* c = createRandomCurve();
		if (c) curves.push_back(c);
	}
	return curves;
}



void RandomCreate::deletedCurve(std::vector<Curve*>& curves)
{
	curves.clear();
}
