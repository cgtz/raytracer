#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"
#include "Film.h"
#include "Sampler.h"


class Scene
{
public:
	std::list<Shape*> allShapes;
	std::list<DirLight> allDirLights;
	std::list<PtLight> allPtLights;
	Camera camera;
	Film film;
	Sampler sampler;
	Sample sample;

	Scene();
private:
	bool closestIntersect(Ray& ray, float& minT, Intersection& closest);
	void raytrace(Ray& ray, int depth, Color* color);
	Color phongShading(Material mat, Intersection intersect);
};

