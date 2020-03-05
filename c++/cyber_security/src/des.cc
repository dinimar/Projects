#include <vector>
#include "des.h"

DES::DES(std::vector<int8_t> key)
{
    if (key.size() == BYTES_NUM)    // if passed key length is 7 bytes 
    {
        // using copy constructor 
        // and assignment operator to inititalize
        key_ = key;                                 // initialize by passed key
    } else                          
    {
        key_ = std::vector<int8_t>(BYTES_NUM, 0);   // initialize by zeros
    }
}