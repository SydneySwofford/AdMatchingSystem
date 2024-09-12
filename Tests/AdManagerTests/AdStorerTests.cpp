#include "pch.h"
#include "CppUnitTest.h"
#include <Windows.h>
#include "../../AdMatchingSystem/AdManager/AdStorer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace Tests
{
	TEST_CLASS(AdStorerTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_createMemoryMapCantOpenFile)
		{
			AdStorer adStorer;
			char* fakeMappedData = "";

			adStorer.parseAndStoreAds(fakeMappedData);
			vector<Ad> resultVector=adStorer.getAllAds();
			int mySize = resultVector.size();

			Assert::AreEqual(0, mySize);

		}

		TEST_METHOD(TC02_TN01_getAllAds)
		{
			AdStorer adStorer;
			char* fakeMappedData = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda3\", 1.5]";

			adStorer.parseAndStoreAds(fakeMappedData);
			vector<Ad> resultVector = adStorer.getAllAds();
			int mySize = resultVector.size();

			Assert::AreEqual(1, mySize);

		}

		TEST_METHOD(TC02_TN02_getAllAdsdata)
		{
			AdStorer adStorer;
			char* fakeMappedData = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda3\", 1.5]";

			adStorer.parseAndStoreAds(fakeMappedData);
			vector<Ad> resultVector = adStorer.getAllAds();
			string expectedKeyword="mazda";

			Assert::IsTrue(resultVector[0].keywords.find(expectedKeyword)!= resultVector[0].keywords.end());
		}

	};
}
