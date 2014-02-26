#pragma once
#include "stdafx.h"
#include "Vector.h"
using namespace std;
class Color {
    public:
		float r, g, b;
		Color(){};
		Color(float r, float g, float b);
		Color operator*(const Color& c);
		Color operator+(const Color& c);
		Color operator*(const float& c);

};
