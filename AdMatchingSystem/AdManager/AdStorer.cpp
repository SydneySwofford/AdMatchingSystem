#include "AdStorer.hpp"
#include <sstream>
#include <vector>

using namespace std;

AdStorer::AdStorer()
{}

AdStorer::~AdStorer()
{}

void AdStorer::parseAndStoreAds(char* mappedData)
{
    istringstream stream(mappedData);
    string line = "";
   
    while (getline(stream,line))
    {
        istringstream lineStream(line);
        Ad ad;
        lineStream >> ad;
        ads.push_back(ad);
    }
}

const vector<Ad>& AdStorer::getAllAds() const
{
    return ads;
}