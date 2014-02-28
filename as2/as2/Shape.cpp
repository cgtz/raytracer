#include "stdafx.h"
#include "Shape.h"



Shape::Shape(void)
{
}

Sphere::Sphere(vec3 center, float radius, Material material) {
	this->center = center;
	this->radius = radius;
	this->material = material;
}

bool Sphere::intersect(Ray& ray, float& tHit, Intersection* intersect) {
	vec3 e = ray.pos;
	vec3 d = ray.dir;

	float a = d*d;
	float b = 2*d*(e - this->center);
	float c = (e - this->center)*(e - this->center) - this->radius*this->radius;

	if (a == 0){
		std::cout << "Ray is just a point!" << std::endl;
		return false;
	}

	float discriminant = b*b - 4*a*c;

	//float tMin = std::numeric_limits<float>::max();
	if (discriminant >= 0){
		float tPos = (-b + sqrt(discriminant)) / 2*a;
		float tNeg = (-b - sqrt(discriminant)) / 2*a;
		tHit = min(tHit, min( tPos, tNeg));
		if (tHit >= ray.tMax || tHit <= ray.tMin) return false;
		intersect->point = ray.evaluate(tHit);
		intersect->normal  = (intersect->point - this->center).normalize();
		intersect->shape = this;
		return true;
	}
	return false; 
}

