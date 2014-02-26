#pragma once
#include "stdafx.h"
#include "CImg.h"
#include "Color.h"
#include "Sampler.h"

class Film
{
public:
	int width, height;
	cimg_library::CImg<float> image;
	Film(){};
	Film(float width, float height);
	void writePixel(Sample sample, Color color);
	void display();
	void writeFile(string filename);
};

