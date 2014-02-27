#include "stdafx.h"
#include "Material.h"


Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->reflect = reflect;
	this->coeff = coeff;
}

