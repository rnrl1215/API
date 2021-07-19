#include<iostream>
#include"CryptoAPIExample.h"
using namespace std;

int main(int argc, char* argv[])
{   
    std::string plainText = "TESTSTRING:123123123";
    std::string encText = "";
    std::string decText = "";

    // encrypt test
    CryptoAPI *crypto = new CryptoAPI();
    crypto->generateKey("/home/skahn/work/key","/home/skahn/work/iv");
    crypto->encryptString(plainText, encText);
    crypto->decryptString(encText, decText);

    cout << "NORMAL TEXT: " << plainText << endl;
    cout << "ENCRYPT TEXT: " << encText << endl;
    cout << "DECRYPT TEXT: " << decText << endl;


    // ket set test
    CryptoAPI *crypto2 = new CryptoAPI();
    std::string decText2;
    crypto2->setKey("/home/skahn/work/key","/home/skahn/work/iv");
    crypto2->decryptString(encText, decText2);
    cout << "SETKEY: DECRYPT TEXT: " << decText2 << endl;

    // decrypt fail test
    std::string decryptFail = "";
    crypto2->generateKey("/home/skahn/work/key2","/home/skahn/work/iv2");
    crypto2->decryptString(encText, decryptFail);
    cout << "SETIDFFKEY: DECRYPT TEXT: " << decryptFail << endl;
}
