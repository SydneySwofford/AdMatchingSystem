#pragma once
#include "IRequest.hpp"
#include <string>

class IQueryStringParser {
public:
    virtual ~IQueryStringParser() = default;
    virtual void parse(const std::string& fullURL, IRequest& request) = 0;
};