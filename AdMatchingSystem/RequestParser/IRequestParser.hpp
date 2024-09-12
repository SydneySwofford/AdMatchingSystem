#pragma once
#include "Request.hpp"
#include <string>

class IRequestParser {
public:
    virtual ~IRequestParser() = default;
    virtual Request parseRequest(const std::string& requestData) = 0;
};
