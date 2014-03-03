#include "stdafx.h"
#include "Material.h"


Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->reflect = reflect;
	this->coeff = coeff;
	this->refract = vec3(0, 0, 0);
	this->refractIndex = 0;
}

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff, vec3 refract, float refractIndex) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->reflect = reflect;
	this->coeff = coeff;
	this->refract = refract;
	this->refractIndex = refractIndex;
}


