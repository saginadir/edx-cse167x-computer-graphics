#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <memory>
#include <vector>
#include "camera.h"
#include "primitive.h"

class Scene
{
public:
	Scene() :width(0),
			height(0),
			camera(nullptr),
			primitives(std::vector<std::shared_ptr<Primitive>>()){};
	void setWidth(int w){ this->width = w; };
	void setHeight(int h){ this->height = h; };
	void setCamera(Camera *camera){ this->camera = std::unique_ptr<Camera>(camera); };
	void addPrimitive(std::shared_ptr<Primitive> p);
	void processToFile(std::string filename);

private:
	struct Color
	{
		int r, g, b;
	};

	int width, height;
	std::unique_ptr<Camera> camera;
	std::vector<std::shared_ptr<Primitive>> primitives;
	Color traceRay(Ray ray);
};

#endif