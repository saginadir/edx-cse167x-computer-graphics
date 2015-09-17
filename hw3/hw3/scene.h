#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

class Scene
{
public:
	Scene(int w, int h) :w(w), h(h){};
	void setCamera(Camera *camera){ this->camera = camera; };

private:
	int w, h;
	Camera *camera;
};

#endif