#include "pch.h"
#include "CppUnitTest.h"
#include "../../AdMatchingSystem/RequestParser/QueryStringParser.cpp"
#include "../../AdMatchingSystem/RequestParser/Request.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

bool isFormatA(const string& fullURL)
{
    return fullURL.find("size=") != std::string::npos &&
        fullURL.find("ad_width=") == std::string::npos &&
        fullURL.find("ad_height=") == std::string::npos;
}

string urlDecode(const string& inputString)
{
    string decoded = "";
    for (size_t i = 0; i < inputString.length(); ++i)
    {
        if (inputString[i] == '%')
        {
            int value = 0;
            stringstream ss;
            ss << std::hex << inputString.substr(i + 1, 2);
            ss >> value;
            decoded += static_cast<char>(value);
            i += 2;
        }
        else if (inputString[i] == '+')
        {
            decoded += ' ';
        }
        else
        {
            decoded += inputString[i];
        }
    }
    return decoded;
}

namespace Tests
{
	TEST_CLASS(QueryStringParserTests)
	{
	public:
		
		TEST_METHOD(TC01_TN01_ParseFunction)
		{
            QueryStringParser parser;
            Request request;
            std::string url = "http://bid.simpli.fi/ck_bid?kw=declutter+rc_summit+pompay+luminator+jewelrywonder+mesothrelioma+nudistsites+matures&user_agent=Mozilla/5.0%20(Windows%20NT%206.1;%20WOW64)%20AppleWebKit/537.17%20(KHTML,%20like%20Gecko)%20Chrome/24.0.1312.57%20Safari/537.17&ip_address=99.230.153.128&size=300x250&site_id=97";
			string expectedKeyword = "declutter";

            parser.parse(url, request);

            Assert::AreEqual(300, request.width);
            Assert::AreEqual(250, request.height);
            Assert::IsTrue(request.keywords.find(expectedKeyword) != request.keywords.end());
		}

        TEST_METHOD(TC02_TN01_IsFormatAFunctionReturnsTrue)
        {
            Request request;
            QueryStringParser parser;
            std::string url = "http://bid.simpli.fi/ck_bid?kw=declutter+rc_summit+pompay+luminator+jewelrywonder+mesothrelioma+nudistsites+matures&user_agent=Mozilla/5.0%20(Windows%20NT%206.1;%20WOW64)%20AppleWebKit/537.17%20(KHTML,%20like%20Gecko)%20Chrome/24.0.1312.57%20Safari/537.17&ip_address=99.230.153.128&size=300x250&site_id=97";
            bool expectedFormat = true;
            bool resultFormat=isFormatA(url);

            Assert::AreEqual(expectedFormat, resultFormat);

        }

        TEST_METHOD(TC02_TN02_IsFormatAFunctionReturnsFalse)
        {
            Request request;
            QueryStringParser parser;
            std::string url = "http://simpli.fi/kal_el?keywords=cars+mazda&ad_width=320&ad_height=250&user_ip=67.10.32.95&browser_agent=Mozilla%2f5.0%20%28compatible%3b%20MSIE%209.0%3b%20Windows%20NT%206.0%3b%20Trident%2f5.0%29";
            bool expectedFormat = false;
            bool resultFormat = isFormatA(url);

            Assert::AreEqual(expectedFormat, resultFormat);

        }

        TEST_METHOD(TC03_TN01_ParseFormatA)
        {
            QueryStringParser parser;
            Request request;
            std::string url = "http://bid.simpli.fi/ck_bid?kw=declutter+rc_summit+pompay+luminator+jewelrywonder+mesothrelioma+nudistsites+matures&user_agent=Mozilla/5.0%20(Windows%20NT%206.1;%20WOW64)%20AppleWebKit/537.17%20(KHTML,%20like%20Gecko)%20Chrome/24.0.1312.57%20Safari/537.17&ip_address=99.230.153.128&size=300x250&site_id=97";
            string expectedKeyword = "declutter";

            parser.parse(url, request);

            Assert::AreEqual(300, request.width);
            Assert::AreEqual(250, request.height);
            Assert::IsTrue(request.keywords.find(expectedKeyword) != request.keywords.end());
        }

        TEST_METHOD(TC03_TN02_ParseFormatANoQueryString)
        {
            QueryStringParser parser;
            Request request;
            std::string url = "http://bid.simpli.fi/ck_bidkw=declutter+rc_summit+pompay+luminator+jewelrywonder+mesothrelioma+nudistsites+matures&user_agent=Mozilla/5.0%20(Windows%20NT%206.1;%20WOW64)%20AppleWebKit/537.17%20(KHTML,%20like%20Gecko)%20Chrome/24.0.1312.57%20Safari/537.17&ip_address=99.230.153.128&size=300x250&site_id=97";
          
            Assert::ExpectException<runtime_error>([&]()
                { parser.parse(url, request); 
                });

        }

        TEST_METHOD(TC04_TN01_ParseFormatB)
        {
            QueryStringParser parser;
            Request request;
            std::string url = "http://simpli.fi/kal_el?keywords=cars+mazda&ad_width=320&ad_height=250&user_ip=67.10.32.95&browser_agent=Mozilla%2f5.0%20%28compatible%3b%20MSIE%209.0%3b%20Windows%20NT%206.0%3b%20Trident%2f5.0%29";
            string expectedKeyword = "mazda";

            parser.parse(url, request);

            Assert::AreEqual(320, request.width);
            Assert::AreEqual(250, request.height);
            Assert::IsTrue(request.keywords.find(expectedKeyword) != request.keywords.end());



        }
        
        TEST_METHOD(TC04_TN02_ParseFormatBNoQueryString)
        {
            QueryStringParser parser;
            Request request;
            std::string url = "http://simpli.fi/kal_elkeywords=cars+mazda&ad_width=320&ad_height=250&user_ip=67.10.32.95&browser_agent=Mozilla%2f5.0%20%28compatible%3b%20MSIE%209.0%3b%20Windows%20NT%206.0%3b%20Trident%2f5.0%29";

            Assert::ExpectException<runtime_error>([&]()
                { parser.parse(url, request);
                });

        }

        TEST_METHOD(TC05_TN01_URLDecode)
        {
            QueryStringParser parser;
            string encoded = "Hello%20World%21";
            string expected = "Hello World!";

            Assert::AreEqual(expected, urlDecode(encoded));

        }


	};
}
