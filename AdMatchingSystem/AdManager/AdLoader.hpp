#include "IAdLoader.hpp"
#include <Windows.h>
#include <stdexcept>

class AdLoader : public IAdLoader {
private:
    HANDLE fileHandle;
    HANDLE fileMapping;

public:
    AdLoader();
    ~AdLoader();

    char* createMemoryMap(const std::string& filePath) override;
};
