#include "stdafx.h"
#include "Camera.h"



Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov, float width, float height, float apR) {
	this->lookFrom = lookFrom;
	this->lookAt = lookAt;
	this->up = up;
	this->fov = fov*PI/180;
	this->apR = apR;
	
	this->width = width;
	this->height = height;
	if (this->fov > PI || this->fov < 0.0) {
		std::cout << "BAD FOV" << std::endl;
		exit(0);
	}
	this->setBoundaries();
}

void Camera::setBoundaries() {
	vec3 viewDirection = this->lookAt - this->lookFrom;
	this->focalDist = viewDirection.length();
	this->hBasis = (viewDirection^this->up).normalize();
	this->vBasis = (hBasis^viewDirection).normalize();
	float halfHeight = tan(this->fov/2) * focalDist;
	//float halfWidth = this->width/2; WROOOOOONG
	//float aspectRatio = halfWidth / halfHeight; WROOOONG
	float aspectRatio =  this->width / this->height; 
	float halfWidth = aspectRatio * halfHeight;

	this->apX = hBasis * this->apR;
	this->apY = vBasis * this->apR;

	this->upperLeft = this->lookAt + vBasis*halfHeight - hBasis*halfWidth;//flipped these
	this->upperRight = this->lookAt + vBasis*halfHeight + hBasis*halfWidth;
	this->lowerLeft = this->lookAt - vBasis*halfHeight -hBasis*halfWidth;
	this->lowerRight = this->lookAt - vBasis*halfHeight + hBasis*halfWidth;
	//cout << "Image Boundaries" << endl;
	//cout << "UL " << upperLeft << endl;
	//cout << "UR "<< upperRight << endl;
	//cout << "LL " << lowerLeft << endl;
	//cout << "LR "<< lowerRight << endl;
}

//Ray Camera::generateRay(Sample s){
//	float halfHeight = tan(this->fov/2) * (this->lookAt - this->lookFrom).mag();
//	float halfWidth = this->width/2;
//	//CAUTION: SAMPLE ORIGIN MIGHT NOT BE CARTESION (LL)
//	Point sampleLoc = this->lookAt + this->vBasis*(s.y-halfHeight) + this->hBasis*(s.x-halfWidth);
//	return Ray(this->lookFrom, sampleLoc - this->lookFrom, 1, std::numeric_limits<float>::max());
//}

Ray Camera::generateRay(vec3 pos) {
	float randx = (rand() / float(RAND_MAX)) * 2 - 1;
	float randy = (rand() / float(RAND_MAX)) * 2 - 1;
	vec3 randEye = this->lookFrom + this->apX*randx + this->apY*randy;
	return Ray(randEye, (pos - randEye).normalize(), 1,POS_INF);
}

vec3 Camera::getPixel(int i, int j) {
	float u = float(i+.5)/width;
	float v = float(j+.5)/height;
	//return (v*lowerLeft+upperLeft*(1-v))*u+(lowerRight*v+upperRight*(1-v))*(1-u); //scalars * vectors
	return u*(v*lowerLeft+(1-v)*upperLeft)+(1-u)*(v*lowerRight+(1-v)*upperRight); 
}

