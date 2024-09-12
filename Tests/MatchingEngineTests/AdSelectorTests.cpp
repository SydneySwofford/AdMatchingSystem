#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/MatchingEngine/AdSelector.cpp"
#include "../../AdMatchingSystem/RequestParser/Request.hpp"
#include "../../AdMatchingSystem/AdManager/AdStorer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(AdSelectorTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_AdSelectorselectNoads)
		{
			AdStorer adStorer;
			char* testMemorySpace="1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";

			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector selector(adStorer);

			Request request;
			request.width = 320;
			request.height = 250;
			request.keywords.insert({ "tech", 0.5 });

			auto selectedAds = selector.selectAds(request);
			Assert::IsTrue(selectedAds.empty());
		}

		TEST_METHOD(TC01_TN02_AdSelectorselectAnAds)
		{
			AdStorer adStorer;
			char* testMemorySpace = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";
;
			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector selector(adStorer);

			Request request;
			request.width = 320;
			request.height = 250;
			request.keywords.insert({ "mazda", 0.5 });

			auto selectedAds = selector.selectAds(request);
			Assert::IsTrue(!selectedAds.empty());
		}

		TEST_METHOD(TC01_TN03_AdSelectorselectKeywordCheck)
		{
			AdStorer adStorer;
			char* testMemorySpace = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";

			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector selector(adStorer);
			string expectedKeyword = "mazda";

			Request request;
			request.width = 320;
			request.height = 250;
			request.keywords.insert({ "mazda", 0.5 });

			auto selectedAds = selector.selectAds(request);
			Assert::IsTrue(selectedAds.at(0).keywords.find(expectedKeyword)!=selectedAds.at(0).keywords.end());
		}
	};
}
