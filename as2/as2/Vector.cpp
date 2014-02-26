#include "stdafx.h"
#include "Vector.h"

using namespace std;
Vector::Vector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z; 
}

Vector Vector::operator+(const Vector& v) {
    Vector temp = *this;
    temp.x = temp.x + v.x;
    temp.y = temp.y + v.y;
    temp.z = temp.z + v.z;
    return temp;
}

Vector Vector::operator-(const Vector& v) {
    Vector temp = *this;
    temp.x = temp.x - v.x;
    temp.y = temp.y - v.y;
    temp.z = temp.z - v.z;
    return temp;
}

Vector Vector::operator*(const float& c) {
	Vector temp = *this;
    temp.x = temp.x * c;
    temp.y = temp.y * c;
    temp.z = temp.z * c;
    return temp;
}

void Vector::operator=(const Vector& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    return;
}

bool Vector::operator==(const Vector& v) {
    return this->x == v.x && this->y == v.y && this->z == v.z;
}

bool Vector::operator!=(const Vector& v) {
    return !(this->x == v.x && this->y == v.y && this->z == v.z);
}

float Vector::mag() {
	return sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
}

Vector Vector::normalize() {
	float length = this->mag();
	if (length != 0) {
		return Vector(this->x/length, this->y/length, this->z/length);
	} else {
		return Vector(0.0f, 0.0f, 0.0f);
	}
}

float Vector::dot(const Vector& v) {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

Vector Vector::cross(const Vector& v) {
	Vector temp;
	temp.x = this->y*v.z - this->z*v.y;
	temp.y = -1*(this->x*v.z - this->z*v.x);
	temp.z = this->x*v.y - this->y*v.x;
	return temp;
}

Vector Vector::operator*(const Vector& v) {
	Vector temp;
	temp.x = this->x *v.x;
	temp.y = this->y *v.y;
	temp.z = this->z *v.z;
	return temp;
}

string Vector::toString() {
    return string("(")+string(to_string(this->x))+string(", ")+string(to_string(this->y))+string(", ")+string(to_string(this->z))+string(")");
}


