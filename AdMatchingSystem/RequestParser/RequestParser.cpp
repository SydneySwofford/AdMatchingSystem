#pragma once
#include<sstream>
#include "RequestParser.hpp"
#include <stdexcept>

using namespace std;

RequestParser::RequestParser(IQueryStringParser& parser)
	:queryStringParser(parser)
{}

RequestParser::~RequestParser()
{}

Request RequestParser::parseRequest(const string& requestData)
{
	Request request;
	istringstream requestStream(requestData);
	string line = "";

	if (getline(requestStream,line))
	{
		queryStringParser.parse(line, request);
	}

	return request;
}

