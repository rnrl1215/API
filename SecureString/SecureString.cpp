#include "SecureString.h"
#include<string.h>
#include<iostream>

std::string
SecureString::toSecString(const std::string& value)
{
    std::string tmpString = value;
    std::string secString = value;

    if (!tmpString.empty()) {
        secString.assign(tmpString.size(), '*');

        int changeRange = -1;
        if (tmpString.size() == 2) {
            changeRange = 1;
        }
        else if (tmpString.size() > 3) {
            changeRange = 3;
        }
        else if (tmpString.size() > 2) {
            changeRange = 2;
        }

        if (changeRange != -1) {
            secString.replace(secString.size() - changeRange, secString.size(),
                tmpString.substr(tmpString.size() - changeRange, tmpString.size()));
        }
    }
    return secString;
}

std::string
SecureString::toSecString(int value)
{
    std::string tmpString = std::to_string(value);
    std::string secString = toSecString(tmpString);

    return secString;
}

std::string
SecureString::toSecString(double value)
{
    std::string tmpString = std::to_string(value);

    // 소수점 처리
    tmpString.erase(tmpString.find_last_not_of('0') + 1, std::string::npos);
    std::string secString = toSecString(tmpString);

    return secString;
}
