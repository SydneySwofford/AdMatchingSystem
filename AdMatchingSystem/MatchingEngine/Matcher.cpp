#include "Matcher.hpp"

using namespace std;

Matcher::Matcher(IAdSelector& selector, IBidCalculator& calculator)
	:adSelector(selector), bidCalculator(calculator)
{}

Matcher::~Matcher()
{}

Ad Matcher::matchAd(const IRequest& request)
{
	auto ads = adSelector.selectAds(request);
	Ad bestAd;
	double bestBid = 0.0;
	for (const auto& ad : ads)
	{
		double bid = bidCalculator.calculateBid(ad, request);
		if (bid > bestBid)
		{
			bestBid = bid;
			bestAd = ad;
		}
	}
	if (bestBid > 0.0)
	{
		bestAd.defaultBid = bestBid;
	}
	else
	{
		bestAd.id = 0;
		bestAd.defaultBid = 0.0;
	}
	return bestAd;
}
