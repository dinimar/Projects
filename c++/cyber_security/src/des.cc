#include <vector>
#include "des.h"

DES::DES(std::array<int8_t, 64> key)
{
    if (key.size() == BYTES_NUM)    // if passed key length is 7 bytes 
    {
        // using copy constructor 
        // and assignment operator to inititalize
        key_ = key;                                 // initialize by passed key
    } else                          
    {
        key_ = std::array<int8_t, BYTES_NUM>();   // initialize by zeros
    }
}