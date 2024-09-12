#include "IBidCalculator.hpp"

class BidCalculator : public IBidCalculator {
public:
	BidCalculator();
	~BidCalculator();
	double calculateBid(const IAd& ad, const IRequest& request) override;
};