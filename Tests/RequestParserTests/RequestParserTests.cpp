#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/RequestParser/RequestParser.cpp"
#include "../../AdMatchingSystem/RequestParser/QueryStringParser.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(RequestParserTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_RequestParser)
		{
			string url = "http://bid.simpli.fi/ck_bid?kw=mazda+cars&size=320x250&ip_address=67.10.32.95&user_agent=Mozilla%2f5.0%20%28compatible%3b%20MSIE%209.0%3b%20Windows%20NT%206.0%3b%20Trident%2f5.0%29";
			Request expectedRequestObbject;
			expectedRequestObbject.height = 250;
			expectedRequestObbject.width = 320;
			expectedRequestObbject.setKeyword("mazda", 0);
			expectedRequestObbject.setKeyword("cars", 0);
			QueryStringParser parser;
			RequestParser requestParser(parser);

			Request outputRequest = requestParser.parseRequest(url);
			Assert::AreEqual(expectedRequestObbject.height, outputRequest.height);
			Assert::AreEqual(expectedRequestObbject.width, outputRequest.width);
		}
	};
}
