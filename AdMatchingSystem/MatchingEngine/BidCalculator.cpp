#include "BidCalculator.hpp"

using namespace std;

BidCalculator::BidCalculator()
{}

BidCalculator::~BidCalculator()
{}

double BidCalculator::calculateBid(const IAd& ad, const IRequest& request)
{
	double maxBid = 0.0;
	bool hasValidBid = false;
	for (const auto& requestKeyword : request.getKeywords())
	{
        if (ad.hasKeyword(requestKeyword.first))
        {
            double keywordBid = ad.getKeywordBid(requestKeyword.first);
            if (keywordBid == 0.0)
            {
                keywordBid = ad.getDefaultBid();
            }
            maxBid = max(maxBid, keywordBid);
            hasValidBid = true;
		}
	}
	return hasValidBid ? maxBid : 0.0;
}