#pragma once
#include "Request.hpp"

using namespace std;

Request::Request()
	:width(0), height(0)
{}

Request::~Request()
{}

void Request::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Request::setKeyword(const string& keyword, int value=0)
{
	keywords[keyword] = value;
}

int Request::getWidth() const
{
	return width;
}

int Request::getHeight() const
{
	return height;
}

void Request::setWidth(int width)
{
	this->width = width;
}
void Request::setHeight(int height)
{
	this->height = height;
}

int Request::getKeywordValue(const std::string& keyword) const
{
	auto it = keywords.find(keyword);
	if (it != keywords.end()) {
		return it->second;
	}
	return 0.0;
}

bool Request::hasKeyword(const std::string& keyword) const
{
	return keywords.find(keyword) != keywords.end();
}

const std::unordered_map<std::string, double>& Request::getKeywords() const
{
	return keywords;
}