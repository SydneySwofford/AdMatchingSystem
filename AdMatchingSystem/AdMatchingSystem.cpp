// AdMatchingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include "AdManager/AdLoader.hpp"
#include "RequestParser/RequestParser.hpp"
#include "RequestParser/QueryStringParser.hpp"
#include "MatchingEngine/AdSelector.hpp"
#include "MatchingEngine/BidCalculator.hpp"
#include "MatchingEngine/Matcher.hpp"
#include "Utilities/OutputGenerator.hpp"
#include "AdManager/AdStorer.hpp"

using namespace std;

int main()
{
    //Utility 
    OutputGenerator outputGenerator("..\\output.txt");

    //Load Ads
    char* mappedMemorySpace;
    AdLoader adLoader;
    AdStorer adStorer;
    mappedMemorySpace = adLoader.createMemoryMap("..\\ads.txt");
    adStorer.parseAndStoreAds(mappedMemorySpace);
    vector<Ad> adVector = adStorer.getAllAds();

    //Read requests "as the come" (but each line from the request log) and output to file
    string filePath = "..\\requests.log";
    ifstream file(filePath);
    AdSelector adSelector(adStorer);
    BidCalculator bidCalculator;
    Matcher matcher(adSelector, bidCalculator);

    if (!file.is_open())
    {
        throw runtime_error("Cannot Open Request File");
    }

    QueryStringParser queryStringParser;
    RequestParser requestParser(queryStringParser);
    string line = "";
    
   while (getline(file, line))
    {
        Request requestObject = requestParser.parseRequest(line);
        Ad bestAd = matcher.matchAd(requestObject);
        outputGenerator.writeOutput(bestAd);
    }
 
}
