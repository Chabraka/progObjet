#include "Loader.hpp"
#include <string>
#include <iostream>
#include <fstream>

void opentest(std::string path){
	std::ifstream file(path);

	std::string line;
	while (std::getline(file, line)){
		std::cout << line << "\n";
	}
}