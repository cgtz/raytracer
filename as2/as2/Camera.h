#pragma once
#include "stdafx.h"
#include "Ray.h"
#include "Sampler.h"
class Camera
{
public:
	Point lookFrom, lookAt;
	Point upperLeft, upperRight, lowerLeft, lowerRight;
	Vector up, hBasis, vBasis;
	float fov, width, height;
	Camera(){};
	Camera(Point lookFrom, Point lookAt, Vector up, float fov, float width, float height);
	
	void setBoundaries();
	Ray generateRay(Sample s);
};

