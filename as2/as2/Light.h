#pragma once
#include "stdafx.h"
#include "Color.h"
#include "Intersection.h"
#include "Ray.h"

//class Light {
//    public:
//        Color color;
//        Point pos;
//        Light(Color, Vector);
//		virtual void generateLightRay(Intersection& intersect, Ray* ray, Color* color){}
//        
//};


class PtLight {
public:
	Color color;
	Point pos;
	PtLight(Color c, Point p);
	void generateLightRay(Intersection& intersect, Ray* ray, Color* color);
};

class DirLight {
public:
	Color color;
	Vector dir;
	DirLight(Color c, Vector v);
	void generateLightRay(Intersection& intersect, Ray* ray, Color* color);
};

