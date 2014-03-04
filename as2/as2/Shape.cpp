#include "stdafx.h"
#include "Shape.h"



Shape::Shape(void)
{
}

Sphere::Sphere(vec3 center, float radius, Transformation& transformation) {
	this->transform = transformation.transform;
	this->transformI = transformation.transformI;
	this->transformTI = transformation.transformTI;

	this->center = center;
	this->radius = radius;
	this->material = Material(vec3(0.2,0.2,0.2), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 1);
}

Sphere::Sphere(vec3 center, float radius, Material material, Transformation& transformation) {
	this->transform = transformation.transform;
	this->transformI = transformation.transformI;
	this->transformTI = transformation.transformTI;

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
		intersect->point = transform * ray.evaluate(tHit);
		intersect->normal  = vec3(transformTI * vec4(intersect->point - this->center, 0),VW).normalize();
		intersect->shape = this;
		return true;
	}
	return false; 
}

Triangle::Triangle(vec3 v1,vec3 v2, vec3 v3, Material material, Transformation& transformation) {
	this->transform = transformation.transform;
	this->transformI = transformation.transformI;
	this->transformTI = transformation.transformTI;

	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->material = material;

	this->n1 = ((v2-v1)^(v3-v1)).normalize();
	this->n2 = n1;
	this->n3 = n1;
}

Triangle::Triangle(vec3 v1,vec3 v2, vec3 v3, vec3 n1, vec3 n2, vec3 n3, Material material, Transformation& transformation) {
	this->transform = transformation.transform;
	this->transformI = transformation.transformI;
	this->transformTI = transformation.transformTI;

	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;

	this->material = material;

	this->n1 = n1.normalize();
	this->n2 = n2.normalize();
	this->n3 = n3.normalize();
}

bool Triangle::intersect(Ray& ray, float& tHit, Intersection* intersect) {
	vec3 eye = ray.pos;
	vec3 dir = ray.dir;

	float a = v1[VX] - v2[VX],  d = v1[VX] - v3[VX],   g = dir[VX];
	float b = v1[VY] - v2[VY],  e = v1[VY] - v3[VY],   h = dir[VY];
	float c = v1[VZ] - v2[VZ],  f = v1[VZ] - v3[VZ],   i = dir[VZ];

	float j = v1[VX]-eye[VX];
	float k = v1[VY]-eye[VY];
	float l = v1[VZ]-eye[VZ];

	float m = (a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g));
	
	float t = (f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/-m;
	if (t < ray.tMin || t > ray.tMax) return false;

	float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / m;
	if (gamma < 0 || gamma > 1) return false;

	float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/m;
	if (beta < 0 || beta > 1-gamma) return false;

	tHit = t;
	intersect->point = transform * ray.evaluate(t);
	intersect->shape = this;
	
	float mag = (v1-intersect->point).length() + (v2-intersect->point).length() + (v3-intersect->point).length();

	intersect->normal = vec3(transformTI * vec4(((v1-intersect->point).length()/mag)*n1 + ((v2-intersect->point).length()/mag)*n2 + ((v3-intersect->point).length()/mag)*n3, 0), VW).normalize();
	
	return true;
}
