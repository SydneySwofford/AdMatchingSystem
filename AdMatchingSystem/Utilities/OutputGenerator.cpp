#include <iomanip>
#include "OutputGenerator.hpp"

using namespace std;

OutputGenerator::OutputGenerator(const string& filename)
{
	outputFile.open(filename);
	if (!outputFile.is_open())
	{
		throw runtime_error("Cannot Open Output File" + filename);
	}
}

OutputGenerator::~OutputGenerator()
{
	if (outputFile.is_open())
	{
		outputFile.close();
	}
}

void OutputGenerator::writeOutput(IAd& ad)
{
	if (outputFile.is_open())
	{
		outputFile << setprecision(1) << fixed;
		outputFile << ad.getId() << ", " << ad.getDefaultBid() << endl;
	}
}