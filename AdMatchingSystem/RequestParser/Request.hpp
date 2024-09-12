#pragma once
#include <unordered_map>
#include <string>
#include "IRequest.hpp"

class Request : public IRequest {
public:
	int width=0;
	int height=0;
	std::unordered_map<std::string, double> keywords;

	Request();
	~Request();

	void setSize(int width, int height) override;
	void setKeyword(const std::string& keyword, int value) override;
	int getWidth() const override;
	int getHeight() const override;
	void setWidth(int width) override;
	void setHeight(int height) override;
	int getKeywordValue(const std::string& keyword) const override;
	bool hasKeyword(const std::string& keyword) const override;
	const std::unordered_map<std::string, double>& getKeywords() const override;
};