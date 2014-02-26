#include "stdafx.h"
#include "Ray.h"


Ray::Ray(Point pos, Vector dir, float tMin, float tMax) {
	this->pos = pos;
	this->dir = dir.normalize();
	this->tMin = tMin;
	this->tMax = tMax;
}

Point Ray::evaluate(float t) {
	if (t <= this->tMin || t >= this->tMax) {
		std::cout << "Bad t, outside of bounds for ray" << std::endl;
		exit(1);
	} else {
		return this->pos + (this->dir*t);
	}
}