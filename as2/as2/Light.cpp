#include "stdafx.h"
#include "Light.h"


//Light::Light(Color c, Vector v) {
//	this->color = c;
//	this->pos = v;
//}

PtLight::PtLight(Color c, Point p) {
	this->color = c;
	this->pos = p;
}

void PtLight::generateLightRay(Intersection& intersect, Ray* ray, Color* color) {
	Point local = intersect.point;
	ray->pos = local;
	ray->dir = (this->pos - local).normalize(); 
	ray->tMin = .001;
	ray->tMax = (this->pos - local).mag(); //distance 
	color->r = this->color.r;
	color->g = this->color.g;
	color->b = this->color.b;

}

DirLight::DirLight(Color c, Vector v) {
	this->color = c;
	this->dir = v.normalize();
}

void DirLight::generateLightRay(Intersection& intersect, Ray* ray, Color* color) {
	ray->pos = intersect.point;
	ray->dir = this->dir.normalize();
	ray->tMin = .001; //might have to adjust epsilon
	ray->tMax = POS_INF;

	color->r = this->color.r;
	color->g = this->color.g;
	color->b = this->color.b;
}