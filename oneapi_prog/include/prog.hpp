#pragma once
#include <string>
#include <array>

static const size_t vecN = 5;
typedef int vecArr[vecN];

class clComputeModule{
public:
    std::string _getDeviceInfo();
    void vecAdd(vecArr a, vecArr b);
};
