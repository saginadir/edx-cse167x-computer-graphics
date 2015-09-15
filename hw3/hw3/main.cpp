#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "vector.h"

const std::string SCENE_PATH = "../hw3/scenes/";

struct camera
{
	Vector center;	//look from
	Vector eye;		//look at
	Vector up;		//up direction of camera
	int fovy;
};

struct output
{
	std::string filename;
	int width, height;
};

int main(int argc, char* argv[])
{
	if (argc == 1){
		std::cout << "error: must specify input scene file";
		std::getchar();
		return 1;
	}

	//open and read from scene file
	std::ifstream inscene;
	
	//build full file path to scene file
	std::stringstream scenefile;
	scenefile << SCENE_PATH << argv[1];
	inscene.open(scenefile.str());

	if (!inscene.is_open()){
		std::cout << "error: could not open scene file " << scenefile.str();
		std::getchar();
		return 1;
	}

	output imout;
	camera cam;

	std::string line, token;
	std::stringstream linestream;

	std::string type;
	const int maxvals = 10; //read up to 10 values in a single line of input from scene file
	float vals[maxvals];
	
	// loop through each line and token
	while (std::getline(inscene, line)){
		std::stringstream tokenizer(line);
		tokenizer >> type; //read in first token which is the type

		//read in the rest of the values from the line
		for (int i = 0; i < maxvals && tokenizer.good(); i++){
			tokenizer >> vals[i];
		}
		
		//skip comments
		if (type.find_first_of('#') != std::string::npos){
			continue;
		}

		if (type == "size"){
			imout.width = (int)vals[0];
			imout.height = (int)vals[1];
		}
		else if (type == "output"){
			imout.filename = vals[1];
		}
		else if (type == "camera"){
			Vector center { vals[0], vals[1], vals[2] };
			cam.center = center;

			Vector eye { vals[3], vals[4], vals[5] };
			cam.eye = eye;

			Vector up { vals[6], vals[7], vals[8] };
			cam.up = up;

			cam.fovy = (int)vals[9];
		}
	}

	std::getchar();
}