#pragma once
#include "stdafx.h"
#include "Ray.h"
class Camera
{
public:
	vec3 lookFrom, lookAt;
	vec3 upperLeft, upperRight, lowerLeft, lowerRight;
	vec3 up, hBasis, vBasis;
	vec3  apX, apY;
	float fov, width, height, focalDist, apR;
	Camera(){};
	Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov, float width, float height, float apR);
	
	void setBoundaries();
	Ray generateRay(vec3 s);
	vec3 getPixel(int i, int j);
};

