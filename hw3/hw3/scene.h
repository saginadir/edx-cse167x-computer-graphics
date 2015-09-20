#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <memory>

#include "camera.h"

class Scene
{
public:
	Scene() :width(0), height(0), camera(nullptr){};
	void setWidth(int w){ this->width = w; };
	void setHeight(int h){ this->height = h; };
	void setCamera(Camera *camera){ this->camera = std::unique_ptr<Camera>(camera); };
	void processToFile(std::string filename);

private:
	int width, height;
	std::unique_ptr<Camera> camera;
};

#endif