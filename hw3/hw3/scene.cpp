#include "scene.h"
#include "FreeImage.h"

#include <iostream>

void Scene::processToFile(std::string filename){
	unsigned char *pixels = new unsigned char[this->w * this->h * 3]; //width * height * number of bytes(r,g,b) per pixel

	for (int i = 0; i < this->w; i++){
		for (int j = 0; j < this->h; j++){
			//shoot ray through pixel

			//find intersection in scene

			//find color and set it on output image
			int pos = (j * this->w) + (i * 3);
			pixels[pos] = 0;		//red
			pixels[pos + 1] = 0;	//green
			pixels[pos + 2] = 0;	//blue
		}
	}

	//save image to file
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, filename.c_str(), 0);
	delete pixels;
}