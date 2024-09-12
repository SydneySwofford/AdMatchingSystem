#pragma once
#include <unordered_map>
#include <string>

class IRequest {
public:
    virtual ~IRequest() = default;

    virtual void setSize(int width, int height) = 0;
    virtual void setKeyword(const std::string& keyword, int value) = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual int getKeywordValue(const std::string& keyword) const = 0;
    virtual bool hasKeyword(const std::string& keyword) const = 0;
    virtual const std::unordered_map<std::string, double>& getKeywords() const = 0;
};