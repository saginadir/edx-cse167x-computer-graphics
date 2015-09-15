#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

const std::string SCENE_PATH = "../hw3/scenes/";

struct vec3
{
	double x, y, z;
};

struct camera
{
	vec3 center;	//look from
	vec3 eye;		//look at
	vec3 up;		//up direction of camera
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
	const int maxvals = 25; //read up to 25 values in a single line of input from scene file
	std::string vals[maxvals];
	
	// loop through each line and token
	while (std::getline(inscene, line)){
		std::stringstream tokenizer(line);
		for (int i = 0; i < maxvals && tokenizer.good(); i++)
			tokenizer >> vals[i];

		//skip comments
		if (vals[0][0] == '#'){
			continue;
		}

		if (vals[0] == "size"){
			imout.width = atoi(vals[1].c_str());
			imout.height = atoi(vals[2].c_str());
		}
		else if (vals[0] == "output"){
			imout.filename = vals[1];
		}
		else if (vals[0] == "camera"){
			vec3 center;
			center.x = atof(vals[1].c_str());
			center.y = atof(vals[2].c_str());
			center.z = atof(vals[3].c_str());
			cam.center = center;

			vec3 eye;
			eye.x = atof(vals[4].c_str());
			eye.y = atof(vals[5].c_str());
			eye.z = atof(vals[6].c_str());
			cam.eye = eye;

			vec3 up;
			up.x = atof(vals[7].c_str());
			up.y = atof(vals[8].c_str());
			up.z = atof(vals[9].c_str());
			cam.up = up;

			cam.fovy = atoi(vals[10].c_str());
		}
	}

	std::getchar();
}