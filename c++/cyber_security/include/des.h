#ifndef DES_H_
#define DES_H_
#include <string>
#include <vector>

class DES
{
private:
    static const int BYTES_NUM = 7;
    std::vector<int8_t> key_;   // key for encryption/decryption
public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(std::vector<int8_t> key);

    DES(const DES & des) = default;
    DES(DES && des) = default;
    DES & operator=(const DES & des) = default;
    DES & operator=(DES && des) = default;
    virtual ~DES() = default;
};

#endif