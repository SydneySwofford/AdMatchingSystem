#pragma once
#include "IRequestParser.hpp"
#include "IQueryStringParser.hpp"
#include <memory>

class RequestParser: public IRequestParser {
private:
	IQueryStringParser& queryStringParser;

public:
	RequestParser(IQueryStringParser& parser);
	~RequestParser();
	Request parseRequest(const std::string& requestData) override;
};