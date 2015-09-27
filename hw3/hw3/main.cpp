#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <stack>

#include "FreeImage.h"
#include "scene.h"
#include "camera.h"
#include "sphere.h"
#include "triangle.h"

const std::string SCENE_PATH = "../hw3/scenes/";

int main(int argc, char* argv[])
{
	//user must provide a scene file
	if (argc == 1){
		std::cout << "error: must specify input scene file";
		std::getchar();
		return 1;
	}

	FreeImage_Initialise(); //init fre

	//open and read from scene file
	std::ifstream inscene;
	
	//build full file path to scene file and open a stream to it
	std::stringstream scenefile;
	scenefile << SCENE_PATH << argv[1];
	inscene.open(scenefile.str());

	//check if file opens
	if (!inscene.is_open()){
		std::cout << "error: could not open scene file " << scenefile.str();
		std::getchar();
		return 1;
	}


	Scene scene;
	std::string outputFilename = "";
	std::vector<glm::vec3> vertexes = std::vector<glm::vec3>();
	std::stack<glm::mat4> transformStack = std::stack<glm::mat4>();
	transformStack.push(glm::mat4(1.0));

	glm::vec3 emission;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;

	std::string line, token;
	std::stringstream linestream;

	const int maxvals = 10;
	float vals[maxvals]; //read up to 10 values in a single line of input from scene file
	
	// loop through each line and token
	while (std::getline(inscene, line)){
		std::stringstream tokenstream(line);
		std::string type;
		tokenstream >> type; //read in first token which is the type

		//skip comments
		if (type.find_first_of('#') != std::string::npos){
			continue;
		}
		//read in filename and save
		else if (type == "output"){
			tokenstream >> outputFilename;
			continue;
		}

		//read in the rest of the values from the line
		for (int i = 0; i < maxvals && tokenstream.good(); i++){
			tokenstream >> vals[i];
		}
		
		if (type == "size"){
			scene.setWidth((int)vals[0]);
			scene.setHeight((int)vals[1]);
		}
		else if (type == "camera"){
			scene.setCamera(new Camera(vals[0], vals[1], vals[2], //look from
									   vals[3], vals[4], vals[5], //look at
									   vals[6], vals[7], vals[8], //up direction
									   (int)vals[9]));			  //fovy
		}
		else if (type == "sphere"){
			std::shared_ptr<Primitive> sphere = std::shared_ptr<Primitive>(new Sphere((int)vals[0], (int)vals[1], (int)vals[2], vals[3]));
			sphere->transform = transformStack.top();
			sphere->ambient = ambient;
			sphere->emission = emission;
			sphere->diffuse = diffuse;
			sphere->specular = specular;
			sphere->shininess = shininess;
			scene.addPrimitive(sphere);
		}
		else if (type == "vertex"){
			vertexes.push_back(glm::vec3(vals[0], vals[1], vals[2]));
		}
		else if (type == "tri"){
			glm::vec3 a, b, c;
			a = vertexes.at((unsigned int)vals[0]);
			b = vertexes.at((unsigned int)vals[1]);
			c = vertexes.at((unsigned int)vals[2]);
			std::shared_ptr<Primitive> tri = std::shared_ptr<Primitive>(new Triangle(a, b, c));
			glm::mat4 trans = transformStack.top();
			tri->transform = transformStack.top();
			tri->ambient = ambient;
			tri->emission = emission;
			tri->diffuse = diffuse;
			tri->specular = specular;
			tri->shininess = shininess;
			scene.addPrimitive(tri);
		}
		else if (type == "pushTransform"){
			transformStack.push(transformStack.top());
		}
		else if (type == "popTransform"){
			transformStack.pop();
		}
		else if (type == "scale"){
			float sx, sy, sz;
			sx = vals[0];
			sy = vals[1];
			sz = vals[2];
			glm::mat4 &top = transformStack.top();
			top = top * glm::mat4(sx, 0, 0, 0,
								  0, sy, 0, 0,
							      0, 0, sz, 0,
							      0, 0, 0, 1);
		}
		else if (type == "translate"){
			float tx, ty, tz;
			tx = vals[0];
			ty = vals[1];
			tz = vals[2];
			glm::mat4 &top = transformStack.top();
			top = top * glm::transpose(glm::mat4(1, 0, 0, tx,
								  0, 1, 0, ty,
								  0, 0, 1, tz,
								  0, 0, 0, 1));
		}
		else if (type == "emission"){
			emission = glm::vec3(vals[0], vals[1], vals[2]);
		}
		else if (type == "diffuse"){
			diffuse = glm::vec3(vals[0], vals[1], vals[2]);
		}
		else if (type == "specular"){
			specular = glm::vec3(vals[0], vals[1], vals[2]);
		}
		else if (type == "ambient"){
			ambient = glm::vec3(vals[0], vals[1], vals[2]);
		}
		else if (type == "shininess"){
			shininess = vals[0];
		}
	}

	scene.processToFile(outputFilename);

	FreeImage_DeInitialise();
}