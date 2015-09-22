#include "scene.h"
#include "ray.h"
#include "FreeImage.h"
#include <iostream>

void Scene::addPrimitive(std::shared_ptr<Primitive> p)
{
	primitives.push_back(p);
}

void Scene::processToFile(std::string filename)
{
	if (camera == nullptr || width == 0 || height == 0){
		std::cout << "Error: invalid scene to process to file\n";
		return;
	}

	BYTE *pixels = new BYTE[width * height * 3]; //width * height * number of bytes(r,g,b) per pixel

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			//shoot ray through pixel
			Ray ray = camera->getRayThruPixel(i, j, width, height);

			//find intersection and its color in scene
			Color color = traceRay(ray);

			//find color and set it on output image
			int pos = (j * width * 3) + (i * 3); //calculate position in array to insert pixel color
			pixels[pos]     = color.b;	//blue
			pixels[pos + 1] = color.g;	//green
			pixels[pos + 2] = color.r;	//red
		}
	}

	//save image to file
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);
	FreeImage_Save(FIF_PNG, img, filename.c_str(), 0);
	delete pixels;
}

Scene::Color Scene::traceRay(Ray ray){
	float minDist = INFINITY;
	std::shared_ptr<Primitive> closestObject = nullptr;

	for (const auto &p : primitives){
		IntersectInfo info = p->intersect(ray);
		if (info.isIntersect && info.distance > 0 && info.distance < minDist){
			closestObject = p;
		}
	}

	struct Color color;
	color.r = closestObject == nullptr ? 0 : 255;
	color.g = 0;
	color.b = 0;
	return color;
}