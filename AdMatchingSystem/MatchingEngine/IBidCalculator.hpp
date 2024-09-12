#pragma once
#include "..\AdManager\IAd.hpp"
#include "..\RequestParser\IRequest.hpp"
#include <vector>

class IBidCalculator {
public:
    virtual ~IBidCalculator() = default;
    virtual double calculateBid(const IAd& ad, const IRequest& request) = 0;
};