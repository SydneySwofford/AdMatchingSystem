#pragma once
#include <vector>
#include "Ad.hpp"

class IAdStorer {
public:
    virtual ~IAdStorer() = default;
    virtual void parseAndStoreAds(char* mappedData) = 0;
    virtual const std::vector<Ad>& getAllAds() const = 0;
};
