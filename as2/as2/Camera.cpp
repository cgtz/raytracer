#include "stdafx.h"
#include "Camera.h"



Camera::Camera(Point lookFrom, Point lookAt, Vector up, float fov, float width, float height) {
	this->lookFrom = lookFrom;
	this->lookAt = lookAt;
	this->up = up;
	this->fov = fov;
	this->width = width;
	this->height = height;
	if (fov > PI || fov < 0) {
		std::cout << "BAD FOV" << std::endl;
		exit(0);
	}
	this->setBoundaries();
}

void Camera::setBoundaries() {
	Vector viewDirection = this->lookAt - this->lookFrom;
	this->hBasis = viewDirection.cross(this->up).normalize();
	this->vBasis = hBasis.cross(viewDirection).normalize();
	float halfHeight = tan(this->fov/2) * (this->lookAt - this->lookFrom).mag();
	float halfWidth = this->width/2;
	float aspectRatio =  halfWidth / halfHeight;

	this->upperLeft = this->lookAt + vBasis*halfHeight - hBasis*halfWidth;
	this->upperRight = this->lookAt + vBasis*halfHeight + hBasis*halfWidth;
	this->lowerLeft = this->lookAt - vBasis*halfHeight -hBasis*halfWidth;
	this->lowerRight = this->lookAt - vBasis*halfHeight + hBasis*halfWidth;
}

Ray Camera::generateRay(Sample s){
	float halfHeight = tan(this->fov/2) * (this->lookAt - this->lookFrom).mag();
	float halfWidth = this->width/2;
	//CAUTION: SAMPLE ORIGIN MIGHT NOT BE CARTESION (LL)
	Point sampleLoc = this->lookAt + this->vBasis*(s.y-halfHeight) + this->hBasis*(s.x-halfWidth);
	return Ray(this->lookFrom, sampleLoc - this->lookFrom, 1, std::numeric_limits<float>::max());
}

