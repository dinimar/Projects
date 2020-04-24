#include "diffie-hellman.h"
#include <openssl/sha.h>
#include <openssl/aes.h>

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

char genRandom()
{
    return alphanum[rand() % stringLength];
}


int main(int argc, char** argv)
{
    // Challenge 33
    using boost::multiprecision::cpp_int;
    using namespace ENCRYPTION::DIFFIE_HELLMAN;

    cpp_int p = 0xffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b22514a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f83655d23dca3ad961c62f356208552bb9ed529077096966d670c354e4abc9804f1746c08ca237327ffffffffffffffff; 
    cpp_int g = 2;

    publicSessionKey(p, g);

    // Challenge 34
    size_t keyLen = 16;
    // A receiver
    // unsigned char aMailBox[keyLen];
    // B receiver
    // unsigned char bMailBox[keyLen];
    // A->B
    // Send p, g, A. Use previously defined p, g
    cpp_int a = xLower(p);
    cpp_int A = modExp(p, g, a);
    // B received A
    cpp_int b = xLower(p);
    cpp_int sB = modExp(A, b, p);   // generate public session key
    // B->A
    // Send B
    cpp_int B = modExp(p, g, b);
    // A received B
    cpp_int sA = modExp(B, a, p);   // generate public session key

    // A->B
    // Send AES-CBC(SHA1(s)[0:16], iv=random(16), msg) + iv
    // initialize AES key
    unsigned char keyBuffer[keyLen];
    const unsigned char * aTmp = reinterpret_cast<const unsigned char*>(sA.str().c_str());
    SHA1(aTmp, 16, keyBuffer);
    AES_KEY encKey;
    AES_set_encrypt_key(keyBuffer, 16, &encKey); 
    // message vars
    const unsigned char * aMsg = reinterpret_cast<unsigned char *>(const_cast<char *>("SOS"));
    // for (size_t i = 0; i < 3; i++)
    //     aMsg[i] = i;
    
    unsigned char * encOut;
    // generate initialization vector
    unsigned char * ivec = new unsigned char[16];
    for(size_t i=0; i<16; i++)
    {
        ivec[i] = genRandom();
    }
    // encryption
    AES_cbc_encrypt(aMsg, encOut, 3, &encKey, ivec, AES_ENCRYPT);
    // append iv to the end
    std::string tmp = reinterpret_cast<const char *>(encOut);
    tmp += reinterpret_cast<const char *>(ivec);
    const unsigned char * conEncOut = reinterpret_cast<const unsigned char *>(tmp.c_str());
    int encLen = tmp.size();

    // B received message
    unsigned char * decOut;
    tmp = reinterpret_cast<const char *>(encOut);
    tmp = tmp.substr(0, tmp.size()-16); // remove appended ivec
    decOut = reinterpret_cast<unsigned char *>(const_cast<char *>(tmp.c_str())); 
    AES_cbc_encrypt(conEncOut, decOut, encLen, &encKey, ivec, AES_DECRYPT);
    // B->A
    // update ivec for a new session
    for(size_t i=0; i<16; i++)
    {
        ivec[i] = genRandom();
    }
    // Send AES-CBC(SHA1(s)[0:16], iv=random(16), A'smsg) + iv
    AES_cbc_encrypt(decOut, encOut, 3, &encKey, ivec, AES_ENCRYPT);
    // append iv to the end
    tmp = reinterpret_cast<const char *>(encOut);
    tmp += reinterpret_cast<const char *>(ivec);
    encOut = reinterpret_cast<unsigned char *>(const_cast<char *>(tmp.c_str()));

    // A received message
    unsigned char * finalDecOut;
    tmp = reinterpret_cast<const char *>(encOut);
    tmp = tmp.substr(0, tmp.size()-16); // remove appended ivec
    encOut = reinterpret_cast<unsigned char *>(const_cast<char *>(tmp.c_str()));
    AES_cbc_encrypt(encOut, finalDecOut, 3, &encKey, ivec, AES_DECRYPT);

    printf("A sent: [%s]", aMsg);
    printf("A received: [%s]", encOut);
    

    return 0;
}