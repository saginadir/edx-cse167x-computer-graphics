#include "scene.h"
#include "ray.h"
#include "FreeImage.h"
#include <iostream>

void Scene::processToFile(std::string filename){
	if (camera == nullptr || width == 0 || height == 0){
		std::cout << "Error: invalid scene to process to file\n";
		return;
	}

	BYTE *pixels = new BYTE[width * height * 3]; //width * height * number of bytes(r,g,b) per pixel

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			//shoot ray through pixel
			Ray ray = camera->getRayThruPixel(i, j, width, height);

			//find intersection in scene

			//find color and set it on output image
			int pos = (j * width * 3) + (i * 3); //calculate position in array to insert pixel color
			pixels[pos] = 0;		//blue
			pixels[pos + 1] = 0;	//green
			pixels[pos + 2] = 0;	//red
		}
	}

	//save image to file
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, filename.c_str(), 0);
	delete pixels;
}