#include <iostream>
#include "IAdSelector.hpp"
#include "IBidCalculator.hpp"
#include "IMatcher.hpp"

class Matcher : public IMatcher {
private:
	IAdSelector& adSelector;
	IBidCalculator& bidCalculator;

public:
	~Matcher();
	Matcher(IAdSelector& selector, IBidCalculator& calculator);
	Ad matchAd(const IRequest& request) override;
};