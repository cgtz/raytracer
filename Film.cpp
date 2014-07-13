#include "stdafx.h"
#include "Film.h"


Film::Film(int width, int height) {
	this->width =width;
	this->height =height;
	this->image.assign(this->width, this->height,1,3,0); //3 channels
}

void Film::writePixel(int i, int j, vec3 color) {
	float red = color[RED], green = color[GREEN], blue = color[BLUE];
	//if (color[RED] > 1.0f){
	//	red = 1.0f;
	//}
	//if (color[GREEN] > 1.0f){
	//	green = 1.0f;
	//}
	//if (color[BLUE] > 1.0f){
	//	blue = 1.0f;
	//}
	const float colorArray[] = {red, green, blue};
	//FIX FOR MULTIPLE SAMPLES IN ONE PIXEL
	this->image.draw_point(width-i , j, colorArray);
}

void Film::display() {
	cimg_library::CImgDisplay disp(image, "RayTracer Output");
	while (true) {
		disp.wait();
	}
}

void Film::writeFile(string filename) {
	image.normalize(0, 255);
	image.save(filename.c_str());
}
