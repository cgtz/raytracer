#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Point.h"
class Ray
{
public:
	Point pos;
	Vector dir;
	float tMin, tMax;
	Ray(){}
	Ray(Point pos, Vector dir, float tMin, float tMax);
	Point evaluate(float t);
};

