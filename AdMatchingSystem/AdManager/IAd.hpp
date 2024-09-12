#pragma once
#include <map>
#include <string>
#include <sstream>
#include <iostream>


class IAd {
public:
	virtual ~IAd()=default;
    virtual int getId() const = 0;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual double getDefaultBid() const = 0;

    virtual void setId(int id) = 0;
    virtual void setWidth(int width) = 0;
    virtual void setHeight(int height) = 0;
    virtual void setDefaultBid(double bid) = 0;

    virtual double getKeywordBid(const std::string& keyword) const = 0;
    virtual void setKeywordBid(const std::string& keyword, double bid) = 0;
    virtual void removeKeyword(const std::string& keyword) = 0;
    virtual bool hasKeyword(const std::string& keyword) const = 0;
    virtual std::map<std::string, double> getAllKeywords() const = 0;

	virtual void display() const=0;
};