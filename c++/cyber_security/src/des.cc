#include <vector>
#include "des.h"

DES::DES(std::array<int8_t, 7> key)
{
    if (key.size() == BYTES_NUM)    // if passed key length is 7 bytes 
    {
        // using copy constructor 
        // and assignment operator to inititalize
        key_.swap(key);                                 // initialize by passed key
    } else                          
    {
        key_ = std::array<int8_t, BYTES_NUM>();   
        key_.fill(0);   // initialize by zeros
    }
}