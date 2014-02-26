#pragma once
#include "stdafx.h"

class Vector {
    public:
        float x,y,z;
		Vector(){};
        Vector(float x, float y, float z);
		
		//operators
        virtual Vector operator+(const Vector& v);
        Vector operator-(const Vector& v);
		Vector operator*(const float& c);
        void operator=(const Vector& v);
        bool operator==(const Vector& v);
        bool operator!=(const Vector& v);

		float mag();
		Vector normalize();
		float dot(const Vector& v);
		Vector cross(const Vector& v);

		Vector operator*(const Vector& v);

        std::string toString();
        
};



