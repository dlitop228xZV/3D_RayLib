#include "RandomCreate.h"
#include <cstdlib>

double RandomCreate::random()
{
	return 1 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (5 - 1)));
}

std::shared_ptr<Curve> RandomCreate::createRandomCurve()
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

std::shared_ptr<Circle> RandomCreate::createRandomCircle()
{
	return std::make_shared<Circle>(random());
}

std::shared_ptr<Ellipse> RandomCreate::createRandomEllipse()
{
	return std::make_shared<Ellipse>(random(), random());
}

std::shared_ptr<Helixes> RandomCreate::createRandomHelix()
{
	return std::make_shared<Helixes>(random(), random());
}

std::vector<std::shared_ptr<Curve>> RandomCreate::createRandomCurves(int count)
{
	std::vector<std::shared_ptr<Curve>> curves;
	for (int i = 0; i < count; i++)
	{
		auto c = createRandomCurve();
		if (c) curves.push_back(c);
	}
	return curves;
}
