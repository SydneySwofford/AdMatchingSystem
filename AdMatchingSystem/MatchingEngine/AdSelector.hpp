#include "IAdSelector.hpp"
#include "../AdManager/IAdStorer.hpp"

class AdSelector: public IAdSelector {
private:
	IAdStorer& adStorer;

public:
	~AdSelector();
	AdSelector(IAdStorer& adStorer);
	std::vector<Ad> selectAds(const IRequest& request) override;
};