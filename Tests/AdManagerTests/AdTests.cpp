#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/AdManager/Ad.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;



namespace Tests
{
	TEST_CLASS(AdTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_Ad)
		{
			int expectedID = 1123;
			int expectedWidth = 230;
			int expectedHeight = 300;
			double expectedDefailtBid=1.0;
			
			Ad ad(1123, 230, 300, 1.0);

			Assert::AreEqual(expectedID, ad.id);
			Assert::AreEqual(expectedWidth, ad.width);
			Assert::AreEqual(expectedHeight, ad.height);
			Assert::AreEqual(expectedDefailtBid, ad.defaultBid);

		}

		TEST_METHOD(TC01_TN02_Ad)
		{
			Ad ad;

			Assert::AreEqual(0, ad.id);
			Assert::AreEqual(0, ad.width);
			Assert::AreEqual(0, ad.height);
			Assert::AreEqual(0.0, ad.defaultBid);
		}

		TEST_METHOD(TC02_TN01_display)
		{
			Ad ad(1, 320, 250, 1.5);
			ad.keywords["sports"] = 0.7;
			ad.keywords["tech"] = 0.3;
			stringstream buffer;
			streambuf* oldCoutStreamBuf = cout.rdbuf();
			cout.rdbuf(buffer.rdbuf());


			ad.display();
			cout.rdbuf(oldCoutStreamBuf);

			string expectedOutput = "Ad ID: 1 Width: 320 Height: 250 Default Bid: 1.5\nKeywords:\n";
			expectedOutput += "sports: 0.7\n";
			expectedOutput += "tech: 0.3\n";

			Assert::AreEqual(expectedOutput, buffer.str());

		}

		TEST_METHOD(TC03_TN01_OperatorOverload)
		{
			stringstream infoStream("1, 320, 250, 1.5, [\"tech\", 0.3, \"sports\", 0.7]");
			Ad ad;

			infoStream >> ad;

			Assert::AreEqual(1, ad.id);
			Assert::AreEqual(320, ad.width);
			Assert::AreEqual(250, ad.height);
			Assert::AreEqual(1.5, ad.defaultBid);
			Assert::AreEqual(0.3, ad.keywords["tech"]);
			Assert::AreEqual(0.7, ad.keywords["sports"]);
		}

		TEST_METHOD(TC04_TN01_SetGetKeywords)
		{
			Ad ad;
			ad.setKeywordBid("tech", 1.5);

			Assert::AreEqual(1.5, ad.getKeywordBid("tech"));
		}

		TEST_METHOD(TC04_TN02_GetKeywords)
		{
			Ad ad;
			ad.setKeywordBid("tech", 1.5);

			Assert::IsTrue(ad.hasKeyword("tech"));
			Assert::IsFalse(ad.hasKeyword("nonexistent"));
		}

		TEST_METHOD(TC05_TN01_DefualtBid)
		{
			Ad ad;
			ad.defaultBid = 2.0;
			ad.setKeywordBid("tech", 0.0);

			Assert::AreEqual(0.0, ad.getKeywordBid("tech"));
		}

	};
}
