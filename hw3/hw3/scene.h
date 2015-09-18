#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <memory>

#include "camera.h"

class Scene
{
public:
	Scene(int w, int h) :w(w), h(h){};
	void setCamera(std::shared_ptr<Camera> camera){ this->camera = camera; };
	void processToFile(std::string filename);

private:
	int w, h;
	std::shared_ptr<Camera> camera;
};

#endif