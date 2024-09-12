#pragma once
#include <string>

class IAdLoader {
public:
    virtual ~IAdLoader() = default;
    virtual char* createMemoryMap(const std::string& filePath) = 0;
};
