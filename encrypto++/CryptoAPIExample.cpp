#include "CryptoAPIExample.h"


CryptoAPI::CryptoAPI()
{
    mKeyLength = 0;
    mIvLength = 0;

    mKey = NULL;
    mIv = NULL;

    try {
        mKey = (byte*)malloc(sizeof(byte) * AES::DEFAULT_KEYLENGTH);
        mIv = (byte*)malloc(sizeof(byte) * AES::BLOCKSIZE);
        mKeyLength = AES::DEFAULT_KEYLENGTH;
        mIvLength = AES::BLOCKSIZE;

        if ( (mKey==NULL) || (mIv == NULL) ||
             (mKeyLength == 0) || (mIvLength == 0) )
        {
            throw SECURITY_EXCEPTION::FAIL_ALLOCATION_BUFFER_EX;
        }

    }
    catch(SECURITY_EXCEPTION e) {
        cout<< "Error Code: " << printExceptionMessage(e) << endl;
    }
}

CryptoAPI::~CryptoAPI()
{
    if (mKey != NULL) {
        free(mKey);
    }

    if (mIv != NULL) {
        free(mIv);
    }
}

bool
CryptoAPI::generateKey(string keyPath, string ivPath)
{

    bool ret = false;
    try {
        // 자동으로 생성된 랜덤 시드 풀
        AutoSeededRandomPool prng;

        // 키 생성
        prng.GenerateBlock(mKey, mKeyLength);
        prng.GenerateBlock(mIv, sizeof(mIv));

        // 단순히 key값을 hexa 값으로 출력 해주는 부분
        // Pretty print key
        /*
        string encoded;
        encoded.clear();
        StringSource(mKey, mKeyLength, true,
            new HexEncoder(new StringSink(encoded)) // HexEncoder
        ); // StringSource
        cout << "key: " << encoded << endl;
        */

        // 초기화 벡터 값을 hexa로 출력해 주는 부분
        // Pretty print iv
        /*
        encoded.clear();
        StringSource(mIv, sizeof(mIv), true,
            new HexEncoder(new StringSink(encoded)) // HexEncoder
        ); // StringSource
        cout << "iv: " << encoded << endl;
        */

        // key 를 파일로 저장
        // 후에 동일 한 키로 암복호화 할 때 필요
        std::ofstream keyFileSteam;
        keyFileSteam.open(keyPath, std::ios::out | std::ios::binary);
        if (keyFileSteam.is_open()) {
            keyFileSteam.write((char*)mKey, mKeyLength);
            keyFileSteam.close();
        } else {
            throw SECURITY_EXCEPTION::FAIL_OPEN_INPUT_FILE_EX;
        }
        

        // iv 초기화 벡터를 파일로 저장
        // 후에 동일 한 키로 암복호화 할 때 필요
        std::ofstream ivFileSteam;
        ivFileSteam.open(ivPath, std::ios::out | std::ios::binary);
        if (ivFileSteam.is_open()) {
            ivFileSteam.write((char*)mIv, mIvLength);
            ivFileSteam.close();
        } else {
            if (keyFileSteam.is_open()) {
                keyFileSteam.close();
            }
            throw SECURITY_EXCEPTION::FAIL_OPEN_OUTPUT_FILE_EX;
        }

        if (mKey == NULL || mIv == NULL) {
            throw SECURITY_EXCEPTION::FAIL_GENERATE_KEY_EX;
        }

        ret = true;
    }
    catch (SECURITY_EXCEPTION e)
    {
        cout<< "Error Code: " << printExceptionMessage(e) << endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
    }

    return ret;
}

// 기존에 파일로 저장한 키를 이용할 경우
bool
CryptoAPI::setKey(string keyPath, string ivPath)
{

    bool ret = false;
    try {
        if (mKey == NULL || mIv == NULL) {
            throw SECURITY_EXCEPTION::FAIL_GENERATE_KEY_EX;
        }

        int keyFileSize = 0;
        ifstream inputKeyfile;
        inputKeyfile.open(keyPath, std::ios::binary | std::ios::in);
        inputKeyfile.seekg(0, ios_base::end);//get binary file length
        keyFileSize = inputKeyfile.tellg();//get binary file length
        inputKeyfile.seekg(0, ios::beg);//get binary file length

        char *keybuffer = new char[keyFileSize];

        inputKeyfile.read(keybuffer, keyFileSize);
        inputKeyfile.close();


        memcpy ( mKey, keybuffer, keyFileSize );
        //mKey = reinterpret_cast<byte*>(keybuffer);
        delete keybuffer;

        if (keyFileSize != AES::DEFAULT_KEYLENGTH) {
            throw SECURITY_EXCEPTION::INVALID_KEY_EX;
        }

        int ivFileSize = 0;
        ifstream inputIvfile;
        inputIvfile.open(ivPath, std::ios::binary | std::ios::in);
        inputIvfile.seekg(0, ios_base::end);//get binary file length
        ivFileSize = inputIvfile.tellg();//get binary file length
        inputIvfile.seekg(0, ios::beg);//get binary file length

        char *ivbuffer = new char[ivFileSize];

        inputIvfile.read(ivbuffer, ivFileSize);
        inputIvfile.close();

        memcpy ( mIv, ivbuffer, ivFileSize );
        //mIv = reinterpret_cast<byte*>(ivbuffer);
        delete ivbuffer;

        if (ivFileSize != AES::BLOCKSIZE) {
            cout<< ivFileSize <<endl;
            throw SECURITY_EXCEPTION::INVALID_KEY_EX;
        }
        ret = true;
    }
    catch (SECURITY_EXCEPTION e)
    {
        cout<< "Error Code: " << printExceptionMessage(e) << endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
    }

    return ret;
}

// 암호화
bool
CryptoAPI::encryptString(const string &inputText, string &outPutText)
{

    bool ret = false;

    try
    {
        if (mKey == NULL || mIv == NULL) {
            throw SECURITY_EXCEPTION::INVALID_KEY_EX;
        }
        
         
        // CBC 방식으로 암호화 
        CBC_Mode< AES >::Encryption e;
        
        // 암호화에 필요한 초기 벡터 값과 키 를 셋팅한다.
        e.SetKeyWithIV(mKey, mKeyLength, mIv);

        // string source를 이용하여 StreamTransformationFilter 타입에 맞춰 변환
        // 즉 암호화 하는 구간.
        
        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s( inputText, true,
            new StreamTransformationFilter(e,
            new StringSink(outPutText)) // StreamTransformationFilter
                ); // StringSource

#if 0
                StreamTransformationFilter filter(e);
                filter.Put((const byte*)plain.data(), plain.size());
                filter.MessageEnd();

                const size_t ret = filter.MaxRetrievable();
                cipher.resize(ret);
                filter.Get((byte*)cipher.data(), cipher.size());
#endif
            ret = true;
        }
        catch (SECURITY_EXCEPTION e) {
            cout<< "Error Code: " << printExceptionMessage(e) << endl;
        }
        catch(const CryptoPP::Exception& e)
        {
                cerr << e.what() << endl;
                return 0;
        }

    return ret;
}

bool
CryptoAPI::decryptString(const string &inputText, string &outPutText)
{
    bool ret = false;
    try
    {
        if (mKey == NULL || mIv == NULL)
        {
            throw SECURITY_EXCEPTION::INVALID_KEY_EX;
        }

        CBC_Mode< AES >::Decryption d;
        d.SetKeyWithIV(mKey, mKeyLength, mIv);

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s(inputText, true,
                        new StreamTransformationFilter(d,
                        new StringSink(outPutText)
                        ) // StreamTransformationFilter
                       ); // StringSource

#if 0
        StreamTransformationFilter filter(d);
        filter.Put((const byte*)cipher.data(), cipher.size());
        filter.MessageEnd();

        const size_t ret = filter.MaxRetrievable();
        recovered.resize(ret);
        filter.Get((byte*)recovered.data(), recovered.size());
#endif
            ret = true;
        }
        catch (SECURITY_EXCEPTION e) {
            cout<< "Error Code: " << printExceptionMessage(e) << endl;
        }
        catch(const CryptoPP::Exception& e)
        {
            cerr << e.what() << endl;
        }

        return ret;
}

int
CryptoAPI::printExceptionMessage(SECURITY_EXCEPTION e)
{
    if (e == SECURITY_EXCEPTION::FAIL_GENERATE_KEY_EX) {
        cout << FAIL_GENERATE_KEY_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::FAIL_ENCRYPT_FILE_EX) {
        cout << FAIL_ENCRYPT_FILE_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::FAIL_DECRYPT_FILE_EX) {
        cout << FAIL_DECRYPT_FILE_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::FAIL_OPEN_INPUT_FILE_EX ) {
        cout << FAIL_OPEN_INPUT_FILE_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::FAIL_OPEN_OUTPUT_FILE_EX) {
        cout << FAIL_OPEN_OUTPUT_FILE_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::FAIL_ALLOCATION_BUFFER_EX) {
        cout << FAIL_ALLOCATION_BUFFER_EX_MSG << endl;
    } else if (e == SECURITY_EXCEPTION::INVALID_KEY_EX) {
        cout << INVALID_KEY_EX_MSG << endl;
    }

    return (int)e;
}
