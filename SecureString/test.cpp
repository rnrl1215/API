// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>
#include "SecureString.h"

int main()
{
    int num1 = 1;
    int num2 = 123;
    int num3 = 12345;

    double doubleNum1 = 1.2;
    double doubleNum2 = 1.23;
    double doubleNum3 = 2.0;
    double doubleNum4 = 123456.123456;

    std::string testString1 = "qweqw421eqwe";
    std::string testString2 = "qw1eqweq3we";
    std::string testString3 = "qwe23qweq2we";
    std::string testString4 = "qweq4weqw123e";

    std::cout << SecureString::toSecString(num1) << std::endl;
    std::cout << SecureString::toSecString(num2) << std::endl;
    std::cout << SecureString::toSecString(num3) << std::endl;

    std::cout << SecureString::toSecString(doubleNum1) << std::endl;
    std::cout << SecureString::toSecString(doubleNum2) << std::endl;
    std::cout << SecureString::toSecString(doubleNum3) << std::endl;
    std::cout << SecureString::toSecString(doubleNum4) << std::endl;

    std::cout << SecureString::toSecString(testString1) << std::endl;
    std::cout << SecureString::toSecString(testString2) << std::endl;
    std::cout << SecureString::toSecString(testString3) << std::endl;
    std::cout << SecureString::toSecString(testString4) << std::endl;

}
