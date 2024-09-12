#pragma once
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "IAd.hpp"


class Ad : public IAd {
public:
	int id=0;
	int width=0;
	int height=0;
	double defaultBid=0;
	std::map<std::string, double> keywords;

	Ad();
	Ad(int id, int width, int height, double defaultBid);
	~Ad();

	int getId() const override;
	int getWidth() const override;
	int getHeight() const override;
	double getDefaultBid() const override;

	void setId(int id) override;
	void setWidth(int width) override;
	void setHeight(int height) override;
	void setDefaultBid(double bid) override;

	double getKeywordBid(const std::string& keyword) const override;
	void setKeywordBid(const std::string& keyword, double bid) override;
	void removeKeyword(const std::string& keyword) override;
	bool hasKeyword(const std::string& keyword) const override;
	std::map<std::string, double> getAllKeywords() const override;

	void display() const override;

	friend std::istream& operator>>(std::istream& in, Ad& ad);
};