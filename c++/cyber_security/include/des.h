#ifndef DES_H_
#define DES_H_
#include <string>

class DES
{
private:
    static const int BYTES_NUM = 7;
    int8_t key_[BYTES_NUM];   // key for encryption/decryption
public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(int8_t key[]);

    DES(const DES & des) = default;
    DES(DES && des) = default;
    DES & operator=(const DES & des) = default;
    DES & operator=(DES && des) = default;
    virtual ~DES() = default;
};

#endif