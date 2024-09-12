#include "QueryStringParser.hpp"
#include <sstream>
#include <string>
#include <stdexcept>
#include <iostream>


using namespace std;

QueryStringParser::QueryStringParser()
{}

QueryStringParser::~QueryStringParser()
{}

void QueryStringParser::parse(const std::string& fullURL, IRequest& request)
{
    if (isFormatA(fullURL))
    {
        parseFormatA(fullURL, request);
    }
    else
    {
        parseFormatB(fullURL, request);
    }
}

bool QueryStringParser::isFormatA(const string& fullURL)
{
    return fullURL.find("size=") != std::string::npos &&
        fullURL.find("ad_width=") == std::string::npos &&
        fullURL.find("ad_height=") == std::string::npos;
}

void QueryStringParser::parseFormatA(const string& fullURL, IRequest& request)
{
    size_t questionMarkIndex = fullURL.find('?');
    if (questionMarkIndex == string::npos)
    {
        throw runtime_error("Cannot locate Query String");
        return;
    }

    string queryString = fullURL.substr(questionMarkIndex + 1);
    istringstream queryStream(queryString);
    string line = "";

    while (std::getline(queryStream, line, '&'))
    {
        size_t delimiterPos = line.find('=');
        string key = line.substr(0, delimiterPos);
        string value = delimiterPos != string::npos ? urlDecode(line.substr(delimiterPos + 1)) : "";

        if (key == "size")
        {
            size_t xIndex = value.find('x');
            if (xIndex != std::string::npos)
            {
                request.setSize(std::stoi(value.substr(0, xIndex)), std::stoi(value.substr(xIndex + 1)));
            }
        }
        else if (key == "kw")
        {
            istringstream keywordStream(value);
            string keyword;
            while (getline(keywordStream, keyword, ' '))
            {
                request.setKeyword(keyword, 0.0);
            }
        }
    }
}

void QueryStringParser::parseFormatB(const string& fullURL, IRequest& request)
{
    size_t questionMarkIndex = fullURL.find('?');
    if (questionMarkIndex == string::npos)
    {
        throw runtime_error("Cannot locate Query String");
        return;
    }

    string queryString = fullURL.substr(questionMarkIndex + 1);
    istringstream queryStream(queryString);
    string line = "";

    while (getline(queryStream, line, '&'))
    {
        size_t delimiterPos = line.find('=');
        string key = line.substr(0, delimiterPos);
        string value = delimiterPos != string::npos ? urlDecode(line.substr(delimiterPos + 1)) : "";

        if (key == "ad_width" && !value.empty())
        {
            request.setWidth(std::stoi(value));
        }
        else if (key == "ad_height" && !value.empty())
        {
            request.setHeight(std::stoi(value));
        }
        else if (key == "keywords")
        {
            istringstream keywordStream(value);
            string keyword;
            while (getline(keywordStream, keyword, ' '))
            {
                request.setKeyword(keyword, 0.0);
            }
        }
    }
}

string QueryStringParser::urlDecode(const string& inputString)
{
	string decoded="";
	for (size_t i = 0; i < inputString.length(); ++i)
	{
		if (inputString[i] == '%') 
        {
			int value=0;
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