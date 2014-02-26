#pragma once
#include "stdafx.h"
#include "Point.h"

class Shape;

class Intersection
{
public:
	Vector normal;
	Point point;
	Shape* shape;
	//Intersection(void);
	Intersection(){};
	Intersection(Vector normal, Point point, Shape* shape);
};

