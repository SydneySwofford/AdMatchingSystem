#pragma once
#include<fstream>
#include "../AdManager/IAd.hpp"

class OutputGenerator {
private:
	std::ofstream outputFile; //overwrite by defualt
public:
	OutputGenerator(const std::string& filename);
	~OutputGenerator();
	void writeOutput(IAd& ad);
};