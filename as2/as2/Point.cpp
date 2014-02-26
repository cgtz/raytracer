#include "stdafx.h"
#include "Point.h"

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Point Point::operator+(const Vector& v) {
    Point temp = *this;
    temp.x = temp.x + v.x;
    temp.y = temp.y + v.y;
    temp.z = temp.z + v.z;
    return temp;
}

Point Point::operator-(const Vector& v) {
    Point temp = *this;
    temp.x = temp.x - v.x;
    temp.y = temp.y - v.y;
    temp.z = temp.z - v.z;
    return temp;
}

void Point::operator=(const Point& p) {
    this->x = p.x;
    this->y = p.y;
    this->z = p.z;
    return;
}

Vector Point::operator-(const Point& p) {
	Vector temp; 
    temp.x = this->x - p.x;
    temp.y = this->y - p.y;
    temp.z = this->z - p.z;
    return temp;
}