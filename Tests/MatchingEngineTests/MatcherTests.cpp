#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/MatchingEngine/Matcher.cpp"
#include "../../AdMatchingSystem/MatchingEngine/AdSelector.hpp"
#include "../../AdMatchingSystem/MatchingEngine/BidCalculator.hpp"
#include "../../AdMatchingSystem/AdManager/AdStorer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(MatcherTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_MatcherMatchADSuccessfully)
		{
			AdStorer adStorer;
			char* testMemorySpace = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";
			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector adSelector(adStorer);
			BidCalculator bidCalculator;
			Matcher matcher(adSelector, bidCalculator);
			Request request;
			request.height = 250;
			request.width = 320;
			request.keywords["outdoor"] = 1.5;
			request.keywords["cars"] = 0;

			Ad bestMatch=matcher.matchAd(request);

			Assert::AreEqual(bestMatch.id, 1234);
		}

		TEST_METHOD(TC01_TN02_MatcherMatchADUnSuccessfully)
		{
			AdStorer adStorer;
			char* testMemorySpace = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";
			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector adSelector(adStorer);
			BidCalculator bidCalculator;
			Matcher matcher(adSelector, bidCalculator);
			Request request;
			request.height = 250;
			request.width = 320;
			request.keywords["outdoor"] = 1.5;
			request.keywords["camp"] = 0;

			Ad bestMatch = matcher.matchAd(request);

			Assert::AreNotEqual(bestMatch.id, 1234);
			Assert::AreEqual(bestMatch.id, 0);
		}

		TEST_METHOD(TC01_TN03_MatcherMatchDefault)
		{
			AdStorer adStorer;
			char* testMemorySpace = "1234, 320, 250, 1.0, [\"mazda\", 0.0, \"cars\", 0.5, \"mazda\3]";
			adStorer.parseAndStoreAds(testMemorySpace);
			AdSelector adSelector(adStorer);
			BidCalculator bidCalculator;
			Matcher matcher(adSelector, bidCalculator);
			Request request;
			request.height = 250;
			request.width = 320;
			request.keywords["outdoor"] = 1.5;
			request.keywords["mazda"] = 0;

			Ad bestMatch = matcher.matchAd(request);

			Assert::AreNotEqual(bestMatch.defaultBid, 0.0);
			Assert::AreEqual(bestMatch.defaultBid, 1.0);
		}


	};
}
