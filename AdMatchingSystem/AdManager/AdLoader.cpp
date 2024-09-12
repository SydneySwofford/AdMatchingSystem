#include "AdLoader.hpp"
#include <Windows.h>
#include <stdexcept>

using namespace std;

AdLoader::AdLoader()
    : fileHandle(nullptr), fileMapping(nullptr) 
{}

AdLoader::~AdLoader() 
{
    if (fileMapping != nullptr) 
    {
        CloseHandle(fileMapping);
    }
    if (fileHandle != nullptr) 
    {
        CloseHandle(fileHandle);
    }
}

    char* AdLoader::createMemoryMap(const std::string& filePath)
    {
        wstring wideFilePath = std::wstring(filePath.begin(), filePath.end());
        fileHandle = CreateFile(wideFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (fileHandle == INVALID_HANDLE_VALUE) 
        {
            throw std::runtime_error("Cannot open ads file properly");
        }

        fileMapping = CreateFileMapping(fileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
        if (fileMapping == nullptr) 
        {
            CloseHandle(fileHandle);
            throw runtime_error("Cannot create file mapping");
        }

        char* fileContent = static_cast<char*>(MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0));
        if (fileContent == nullptr) 
        {
            CloseHandle(fileMapping);
            CloseHandle(fileHandle);
            throw runtime_error("Cannot map view of file");
        }

        return fileContent;
    }
