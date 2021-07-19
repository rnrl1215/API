#include <crypto++/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <crypto++/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <crypto++/aes.h>
using CryptoPP::AES;

#include <crypto++/ccm.h>
using CryptoPP::CBC_Mode;

#include <assert.h>

class CryptoAPI {
private:
    byte *mKey;
    byte *mIv;
    int mKeyLength;
    int mIvLength;

    const string FAIL_GENERATE_KEY_EX_MSG = "fali to generate key";
    const string FAIL_ENCRYPT_FILE_EX_MSG = "fail to encrypt file";
    const string FAIL_DECRYPT_FILE_EX_MSG = "fail to decrypt file";
    const string FAIL_OPEN_INPUT_FILE_EX_MSG  = "fail to open input file";
    const string FAIL_OPEN_OUTPUT_FILE_EX_MSG = "fali to open output file";
    const string FAIL_ALLOCATION_BUFFER_EX_MSG = "fail to allocate buffer";
    const string INVALID_KEY_EX_MSG = "The key is invalid";


public:
    enum class SECURITY_EXCEPTION {
        NO_EXCEPTION_EX,
        FAIL_GENERATE_KEY_EX,
        FAIL_ENCRYPT_FILE_EX,
        FAIL_DECRYPT_FILE_EX,
        FAIL_OPEN_INPUT_FILE_EX,
        FAIL_OPEN_OUTPUT_FILE_EX,
        FAIL_ALLOCATION_BUFFER_EX,
        INVALID_KEY_EX
    };

    CryptoAPI();
    ~CryptoAPI();
    bool generateKey(string keyPath, string ivPath);
    bool encryptString(const string &inputText, string &outPutText);
    bool decryptString(const string &inputText, string &outPutText);
    bool setKey(string keyPath, string ivPath);

    int printExceptionMessage(SECURITY_EXCEPTION e);
};
