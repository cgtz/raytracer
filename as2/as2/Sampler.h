#pragma once
#include "stdafx.h"

class Sample {
	public:
		float x, y;
		Sample(){}
		Sample(float x, float y){
			this->x = x;
			this->y = y;
		}
		std::string toString();
};

class Sampler {
	public:
		Sampler(){}
		Sampler(float xMax, float yMax, float increment = 1);
		bool generateSample(Sample& sample);
	private:
		float xMax, yMax, increment;
};



