#ifndef SECURE_STRING
#define SECURE_STRING

#include<iostream>
#include <string>

class SecureString {

public:
    SecureString() {};
    static std::string toSecString(const std::string& value);
    static std::string toSecString(int value);
    static std::string toSecString(double value);

};

#endif
