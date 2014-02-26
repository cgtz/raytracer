#pragma once
#include "stdafx.h"
#include "Color.h"

class Material
{
public:
	Color ambient, diffuse, specular;
	float coeff;
	Material(){};
	Material(Color ambient, Color diffuse, Color specular, float coeff);
};

