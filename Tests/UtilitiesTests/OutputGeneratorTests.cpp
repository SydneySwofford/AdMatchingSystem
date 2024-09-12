#include "pch.h"
#include <iomanip>
#include <fstream>
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/Utilities/OutputGenerator.cpp"
#include "../../AdMatchingSystem/AdManager/Ad.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(OutputGeneratorTests)
	{
	public:

		TEST_METHOD(TC01_TN01_OutputGeneratorInvalidInput)
		{
			string invalidPath = "Z:\\nonexistent\\test_output.txt";

			auto func = [&]() { OutputGenerator outputGenerator(invalidPath); };
			Assert::ExpectException<std::runtime_error>(func);
		}

		TEST_METHOD(TC01_TN02_OutputGenerator)
		{
			string testFilename = "testfile.txt";
			Ad ad{ 1, 320, 250, 1.5 }; 

			OutputGenerator outputGenerator(testFilename);
			outputGenerator.writeOutput(ad);

			ifstream file(testFilename);
			string content;
			getline(file, content);
			file.close();

			string expectedContent = "1, 1.5";

			Assert::AreEqual(expectedContent, content);

			remove(testFilename.c_str());
		}

	};
}
