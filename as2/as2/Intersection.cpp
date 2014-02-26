#include "stdafx.h"
#include "Intersection.h"


Intersection::Intersection(Vector normal, Point point, Shape* shape){
		this->normal = normal.normalize();
		this->point = point;
		this->shape = shape;
}
