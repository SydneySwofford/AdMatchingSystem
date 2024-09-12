#include "pch.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include "../../AdMatchingSystem/AdManager/AdLoader.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace Tests
{
	TEST_CLASS(AdLoaderTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_createMemoryMapCantOpenFile)
		{
			AdLoader adLoader;
			string url = "not_a_real_URL";

			Assert::ExpectException<runtime_error>([&](){adLoader.createMemoryMap(url); });
		}

	};
}
