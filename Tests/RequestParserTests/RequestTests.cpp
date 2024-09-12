#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/RequestParser/Request.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace Tests
{
	TEST_CLASS(RequestTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_RequestObject)
		{
			Request request;

			Assert::AreEqual(request.width, 0);
			Assert::AreEqual(request.height, 0);
		}

		TEST_METHOD(TC02_TN01_SetSize)
		{
			Request request;
			request.setSize(300, 200);

			Assert::AreEqual(request.width, 300);
			Assert::AreEqual(request.height, 200);
		}

		TEST_METHOD(TC03_TN01_SetKeyword)
		{
			string url = "http://bid.simpli.fi/ck_bid?kw=mazda+cars&size=320x250&ip_address=67.10.32.95&user_agent=Mozilla%2f5.0%20%28compatible%3b%20MSIE%209.0%3b%20Windows%20NT%206.0%3b%20Trident%2f5.0%29";
			Request request;
			string keyword1 = "chair";
			string keyword2 = "table";

			request.setKeyword(keyword1, 0);
			request.setKeyword(keyword2);


			Assert::IsTrue(request.keywords.find(keyword1) !=request.keywords.end());
			Assert::IsTrue(request.keywords.find(keyword2) != request.keywords.end());
			Assert::AreEqual(request.keywords[keyword2],0.0);
		}

		TEST_METHOD(TC04_TN01_SetSize)
		{
			Request request;
			request.setSize(1920, 1080);

			Assert::AreEqual(1920, request.getWidth());
			Assert::AreEqual(1080, request.getHeight());
		}

		TEST_METHOD(TC05_TN01_SetGetKeyword)
		{
			Request request;
			request.setKeyword("priority", 100);

			Assert::AreEqual(100, request.getKeywordValue("priority"));
			Assert::IsTrue(request.hasKeyword("priority"));
		}

		TEST_METHOD(TC05_TN02_GetKeywordsNone)
		{
			Request request;
			request.setKeyword("priority", 100);

			Assert::AreEqual(100, request.getKeywordValue("priority"));
			Assert::IsFalse(request.hasKeyword("nonexistent"));
		}
	};
}
