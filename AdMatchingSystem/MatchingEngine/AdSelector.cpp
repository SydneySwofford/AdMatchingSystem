#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "AdSelector.hpp"	

using namespace std;

AdSelector::AdSelector(IAdStorer& adStorer)
	:adStorer(adStorer)
{}

AdSelector::~AdSelector()
{}

vector<Ad> AdSelector::selectAds(const IRequest& request)
{
	vector<Ad> selectedAds;
	for (const auto& ad : adStorer.getAllAds())
	{
		if (ad.width == request.getWidth() && ad.height == request.getHeight())
		{
			for (const auto& keyword : request.getKeywords())
			{
				if (ad.keywords.find(keyword.first) != ad.keywords.end())
				{
					selectedAds.push_back(ad);
					break;
				}
			}
		}
	}
	return selectedAds;
}