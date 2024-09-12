#pragma once
#include "..\RequestParser\IRequest.hpp"
#include "..\AdManager/Ad.hpp"
#include <vector>

class IAdSelector {
public:
    virtual ~IAdSelector() = default;
    virtual std::vector<Ad> selectAds(const IRequest& request) = 0;
};