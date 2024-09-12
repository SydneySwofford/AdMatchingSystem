#pragma once
#include "..\RequestParser\Request.hpp"
#include "..\AdManager\Ad.hpp"

class IMatcher {
public:
    virtual ~IMatcher() = default;
    virtual Ad matchAd(const IRequest& request) = 0;
};