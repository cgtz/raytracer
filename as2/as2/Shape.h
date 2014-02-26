#pragma once
#include "stdafx.h"
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"

class Shape
{
public:
	Material material;
	Shape(void);
	virtual bool intersect(Ray& ray, float& tHit, Intersection * intersect){return false;};
};

class Sphere: public Shape {
public:
	Point center;
	float radius;
	Sphere(Point center, float radius, Material material);
	bool intersect(Ray& ray, float& tHit, Intersection* intersect);

};

