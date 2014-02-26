#include "stdafx.h"
#include "Sampler.h"

std::string Sample::toString() {
	return "( " + std::to_string(this->x)  + ", " + std::to_string(this->y) + ")";
}

Sampler::Sampler(float xMax, float yMax, float increment){
	this->xMax = xMax;
	this->yMax = yMax;
	this->increment = increment;
}

bool Sampler::generateSample(Sample& sample) {
	if (sample.y <= yMax) {
		if (sample.x+increment <= xMax) {
			sample.x += increment;
		} else {
			sample.y += increment;
			sample.x = 0.0f;
			if (sample.y > yMax) {
				return false;
			}
		}

		return true;
	} else {
		return false;
	}
	
}