#include "stdafx.h"
#include "Transformation.h"


Transformation::Transformation() {
	this->transform = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(0,0,0,1));
	this->transformTI = this->transform; //(this->transform.inverse()).transpose();
}

void Transformation::push() {
	pastTransform.push(transform);
}

void Transformation::pop() {
	this->transform = pastTransform.top();
	this->transformTI = this->transform.inverse().transpose();
	pastTransform.pop();
}

void Transformation::translate(vec3 offset) {
	this->transform = translation3D(offset) * transform;
	this->transformTI = this->transform.inverse().transpose();
}

void Transformation::scale(vec3 scale) {
	this->transform = scaling3D(scale) * transform;
	this->transformTI = this->transform.inverse().transpose();
}

void Transformation::rotate(vec3 axis, float angle) {
	this->transform = rotation3D(axis, angle) * transform;
	this->transformTI = this->transform.inverse().transpose();
}
