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
	vec3 center;
	float radius;
	Sphere(vec3 center, float radius, Material material);
	bool intersect(Ray& ray, float& tHit, Intersection* intersect);

};

