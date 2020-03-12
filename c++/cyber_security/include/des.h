#ifndef DES_H_
#define DES_H_
#include <string>
#include <array>

class DES
{
private:
    static const int BYTES_NUM = 7;
    std::array<int8_t, BYTES_NUM> key_;   // key for encryption/decryption
public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(std::array<int8_t, 64> key);

    DES(const DES & des) = default;
    DES(DES && des) = default;
    DES & operator=(const DES & des) = default;
    DES & operator=(DES && des) = default;
    virtual ~DES() = default;
};

#endif