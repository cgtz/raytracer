#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"
#include "Film.h"



class Scene
{
public:
	std::list<Shape*> allShapes;
	std::list<DirLight> allDirLights;
	std::list<PtLight> allPtLights;
	Camera camera;
	Film film;
	Scene();
	void render();
	bool closestIntersect(Ray& ray, float& minT, Intersection& closest);
	void raytrace(Ray& ray, int depth, vec3* color);
	vec3 phongShading(Material mat, Intersection intersect);
	
};

