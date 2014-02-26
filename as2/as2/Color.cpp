#include "stdafx.h"
#include "Color.h"


Color::Color(float red, float green, float blue) {
    this->r = red;
    this->g = green;
    this->b= blue; 
}
//
//string Color::toString() {
//	return string("(")+string(to_string(this->r))+string(", ")+string(to_string(this->g))+string(", ")+string(to_string(this->b))+string(")");
//}

Color Color::operator*(const Color& c) {
	Color temp;
	temp.r = this->r *c.r;
	temp.g = this->g *c.g;
	temp.b = this->b *c.b;
	return temp;
}

Color Color::operator+(const Color& c) {
	Color temp;
	temp.r = this->r + c.r;
	temp.g = this->g + c.g;
	temp.b = this->b + c.b;
	return temp;
}

Color Color::operator*(const float& c) {
	Color temp;
	temp.r = this->r + c;
	temp.g = this->g + c;
	temp.b = this->b + c;
	return temp;
}