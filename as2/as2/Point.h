#pragma once
#include "stdafx.h"
#include "Vector.h"

class Point {
	public:
		float x,y,z;
		Point(){};
		Point(float x, float y, float z);
		Point operator+(const Vector& v);
        Point operator-(const Vector& v);
		Vector operator-(const Point& p);
        void operator=(const Point& v);
};