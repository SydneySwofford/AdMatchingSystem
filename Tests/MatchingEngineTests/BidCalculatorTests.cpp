#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/MatchingEngine/BidCalculator.cpp"
#include "../../AdMatchingSystem/RequestParser/Request.hpp"
#include "../../AdMatchingSystem/AdManager/Ad.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(BidCalculatorTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_BidCalculatorValid)
		{
			BidCalculator bidCalculator;
			Ad ad(1233,350,200,1.0);
			ad.keywords["tech"] = 0.6;
			Request request;
			request.height = 350;
			request.width = 200;
			request.keywords["tech"] = 0;
			request.setKeyword("gym", 0);

			double bidValue=bidCalculator.calculateBid(ad,request);

			Assert::AreEqual(bidValue, ad.keywords.at("tech"));
		}

		TEST_METHOD(TC01_TN02_BidCalculatorDefaultBid)
		{
			BidCalculator bidCalculator;
			Ad ad(1233, 350, 200, 1.0);
			ad.keywords["tech"] = 0.0;
			Request request;
			request.height = 350;
			request.width = 200;
			request.keywords["tech"] = 0;
			request.setKeyword("gym", 0);

			double bidValue = bidCalculator.calculateBid(ad, request);

			Assert::AreNotEqual(bidValue, ad.keywords.at("tech"));
		}


		TEST_METHOD(TC01_TN03_BidCalculatorNoValidBid)
		{
			BidCalculator bidCalculator;
			Ad ad(1233, 350, 200, 1.0);
			ad.keywords["tech"] = 0.6;
			Request request;
			request.height = 350;
			request.width = 200;
			request.keywords["swimming"] = 0;
			request.setKeyword("gym", 0);

			double bidValue = bidCalculator.calculateBid(ad, request);

			Assert::AreNotEqual(bidValue, ad.keywords.at("tech"));
		}

	};
}
