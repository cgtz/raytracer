#include "stdafx.h"
#include "Material.h"


Material::Material(Color ambient, Color diffuse, Color specular, float coeff) {
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->coeff = coeff;
}

