#include "IAdStorer.hpp"
#include <sstream>
#include <vector>
#include "Ad.hpp"

class AdStorer : public IAdStorer {
private:
    std::vector<Ad> ads;

public:
    AdStorer();
    ~AdStorer();
    void parseAndStoreAds(char* mappedData) override;
    const std::vector<Ad>& getAllAds() const override;
};
