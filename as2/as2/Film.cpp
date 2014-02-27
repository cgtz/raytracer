#include "stdafx.h"
#include "Film.h"


Film::Film(int width, int height) {
	this->width =width;
	this->height =height;
	this->image.assign(this->width, this->height,1,3,0); //3 channels
}

void Film::writePixel(int i, int j, vec3 color) {
	const float colorArray[] = {color[RED], color[GREEN], color[BLUE]};
	//FIX FOR MULTIPLE SAMPLES IN ONE PIXEL
	this->image.draw_point(i , j, colorArray);
}

void Film::display() {
	cimg_library::CImgDisplay disp(image, "Hah");
	while (true) {
		disp.wait();
	}
}

void Film::writeFile(string filename) {
	image.normalize(0, 255);
	image.save(filename.c_str());
}
