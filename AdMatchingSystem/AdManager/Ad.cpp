#include <iostream>
#include <string>
#include <map>
#include<iomanip>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Ad.hpp"

using namespace std;

Ad::Ad()
    :id(0), width(0), height(0), defaultBid(0)
{}

Ad::Ad(int id, int width, int height, double defaultBid)
    :id(id), width(width), height(height), defaultBid(defaultBid)
{} 

int Ad::getId()const
{
    return this->id;
}

int Ad::getWidth() const
{
    return this->width;
}

int Ad::getHeight() const
{
    return this->height;
}

double Ad::getDefaultBid() const
{
    return this->defaultBid;
}

void Ad::setId(int id)
{
    this->id = id;
}

void Ad::setWidth(int width)
{
    this->width = width;
}

void Ad::setHeight(int height)
{
    this->height = height;
}

void Ad::setDefaultBid(double bid)
{
    this->defaultBid = bid;
}

double Ad::getKeywordBid(const string& keyword) const
{
    auto it = keywords.find(keyword);
    if (it != keywords.end()) {
        return it->second;
    }
    return 0.0; //doesnt exist
}

void Ad::setKeywordBid(const string& keyword, double bid)
{
    keywords[keyword] = bid;
}

void Ad::removeKeyword(const string& keyword)
{
    keywords.erase(keyword);
}

bool Ad::hasKeyword(const string& keyword) const
{
    return keywords.find(keyword) != keywords.end();
}

std::map<string, double> Ad::getAllKeywords() const
{
    return keywords;
}

Ad::~Ad()
{}

void Ad::display()const
{
    cout << "Ad ID: " << id << " Width: " << width << " Height: " << height << " Default Bid: " << defaultBid << "\nKeywords:\n";
    for (const auto& keyword : keywords) 
    {
        std::cout << keyword.first << ": " << keyword.second << "\n";
    }
}

istream& operator>>(istream& in, Ad& ad)
{
    //basic info
    string line;
    if (getline(in, line))
    {
        istringstream ss(line);
        char comma;

        if (!(ss >> ad.id >> comma >> ad.width >> comma >> ad.height >> comma >> ad.defaultBid >> comma))
        {
            throw runtime_error("Cannot parse ad details");
        }

        //keyword&bid info
        string keywordString;
        if (getline(ss, keywordString, ']'))
        {
            size_t startPosition = keywordString.find('[');
            if (startPosition != string::npos)
            {
                keywordString = keywordString.substr(startPosition + 1);
            }

            istringstream keywordStream(keywordString);
            string keyword;
            double bid;

            while (keywordStream >> std::ws, keywordStream >> std::quoted(keyword) >> comma >> bid)
            {
                ad.keywords[keyword] = bid;
                if (keywordStream.peek() == ',')
                {
                    keywordStream.ignore();
                }

            }
        }
        else
        {
            throw runtime_error("Cannot Parse Keywords");
        }
    }

    return in;
}