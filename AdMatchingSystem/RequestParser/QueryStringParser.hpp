#pragma once
#include <map>
#include <string>
#include "IQueryStringParser.hpp"

class QueryStringParser: public IQueryStringParser {
public:
	QueryStringParser();
	~QueryStringParser();
	void parse(const std::string& fullURL, IRequest& request) override;

private:
	bool isFormatA(const std::string& fullURL);
	void parseFormatA(const std::string& fullURL, IRequest& request);
	void parseFormatB(const std::string& fullURL, IRequest& request);
	std::string urlDecode(const std::string& string);
};