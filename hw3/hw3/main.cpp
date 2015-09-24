#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "FreeImage.h"
#include "scene.h"
#include "camera.h"
#include "sphere.h"

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
	std::vector<Vector> vertexes = std::vector<Vector>();
	Vector *vertexes;

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
			std::shared_ptr<Primitive> sphere = std::shared_ptr<Primitive>(new Sphere(vals[0], vals[1], vals[2], vals[3]));
			scene.addPrimitive(sphere);
		}
		else if (type == "vertex"){
			vertexes.push_back(Vector(vals[0], vals[1], vals[2]));
		}
	}

	scene.processToFile(outputFilename);

	FreeImage_DeInitialise();
}