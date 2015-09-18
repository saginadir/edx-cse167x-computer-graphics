#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "scene.h"
#include "camera.h"

const std::string SCENE_PATH = "../hw3/scenes/";

int main(int argc, char* argv[])
{
	//user must provide a scene file
	if (argc == 1){
		std::cout << "error: must specify input scene file";
		std::getchar();
		return 1;
	}

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

	std::unique_ptr<Scene> scene = nullptr;
	std::shared_ptr<Camera> camera = nullptr;
	std::string outputFilename;

	std::string line, token;
	std::stringstream linestream;

	const int maxvals = 10; //read up to 10 values in a single line of input from scene file
	float vals[maxvals];
	
	// loop through each line and token
	while (std::getline(inscene, line)){
		std::stringstream tokenstream(line);
		std::string type;
		tokenstream >> type; //read in first token which is the type

		//read in the rest of the values from the line
		for (int i = 0; i < maxvals && tokenstream.good(); i++){
			tokenstream >> vals[i];
		}
		
		//skip comments
		if (type.find_first_of('#') != std::string::npos){
			continue;
		}
		else if (type == "size"){
			scene = std::unique_ptr<Scene>(new Scene((int)vals[0], (int)vals[1]));
		}
		else if (type == "output"){
			outputFilename = vals[1];
		}
		else if (type == "camera"){
			camera = std::shared_ptr<Camera>(new Camera(vals[0], vals[1], vals[2], //look from
														vals[3], vals[4], vals[5], //look at
														vals[6], vals[7], vals[8], //up direction
														vals[9]));				   //fovy
		}
	}

	if (scene != nullptr){
		scene->setCamera(camera);
		scene->processToFile(outputFilename);
	}
}