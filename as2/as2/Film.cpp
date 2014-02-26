#include "stdafx.h"
#include "Film.h"


Film::Film(float width, float height) {
	this->width = static_cast<int>(width);
	this->height = static_cast<int>(height);
	this->image = image(this->width, this->height,1,3,0);
}

void Film::writePixel(Sample sample, Color color) {
	const float colorArray[] = {color.r, color.g, color.b};
	//FIX FOR MULTIPLE SAMPLES IN ONE PIXEL
	this->image.draw_point(static_cast<int>(sample.x), static_cast<int>(sample.y), colorArray);
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
