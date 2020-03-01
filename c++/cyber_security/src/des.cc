#include "des.h"

DES::DES(int8_t key[])
{
    // TODO: check size of passing array
    // FIX: add bytes in reverse order
    for (size_t n = 0; n < BYTES_NUM; n++)
        key_[n] = key[n];
}