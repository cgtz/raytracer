#pragma once
#include "stdafx.h"
#include "Intersection.h"
#include "Ray.h"
#include "Material.h"
#include "Transformation.h"

class Shape
{
public:
	Material material;
	mat4 transform, transformI, transformTI;
	bool isSphere;

	Shape(void);
	virtual bool intersect(Ray& ray, float& tHit, Intersection * intersect){return false;};
	virtual bool intersect(Ray& ray){return false;};
};

class Sphere: public Shape {
public:
	vec3 center;
	float radius;
	Sphere(vec3 center, float radius, Transformation& transformation);
	Sphere(vec3 center, float radius, Material material, Transformation& transformation);
	bool intersect(Ray& ray, float& tHit, Intersection* intersect);
	bool intersect(Ray& ray);
};

class Triangle: public Shape {
public:
	vec3 v1, v2, v3;
	vec3 n1, n2, n3;
	Triangle(vec3 v1,vec3 v2, vec3 v3, Material material, Transformation& transformation);
	Triangle(vec3 v1,vec3 v2, vec3 v3, vec3 n1, vec3 n2, vec3 n3, Material material, Transformation& transformation);
	bool intersect(Ray& ray, float& tHit, Intersection* intersect);
	bool intersect(Ray& ray);
};