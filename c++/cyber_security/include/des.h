#ifndef DES_H_
#define DES_H_
#include <string>

class DES
{
private:
    std::string key_;   // key for encryption/decryption
public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(std::string key): key_(key) {};
    
    DES(const DES & des) = default;
    DES(DES && des) = default;
    DES & operator=(const DES & des) = default;
    DES & operator=(DES && des) = default;
    virtual ~DES() = default;
};



#endif