#pragma once
#include "stdafx.h"


class Material
{
public:
	vec3 ambient, diffuse, specular, reflect, refract;
	float coeff, refractIndex;
	Material(){};
	Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff);
	Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff, vec3 refract, float refractIndex);
};

