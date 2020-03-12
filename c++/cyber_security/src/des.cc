#include "des.h"

int64_t DES::get_nth_bit(int n, int64_t data)
{
    return (data >> n) & 1; // shift bits and mask
}

int64_t DES::init_permutate(int64_t data)
{
    int64_t perm_data = 0;  // zero-initialized permutated data
    int k = 0;              // multiplier for bits

    for (int & a: init_table)
    {
        perm_data += get_nth_bit(k, data) << a; // bit shifting by 0, 1 till 63 bits
        ++k;
    }
}

int64_t DES::final_permutate(int64_t data)
{
    int64_t perm_data = 0;  // zero-initialized permutated data
    int k = 0;              // multiplier for bits

    for (int & a: final_table)
    {
        perm_data += get_nth_bit(k, data) << a; // bit shifting by 0, 1 till 63 bits
        ++k;
    }
}

int64_t DES::encrypt(int64_t data)
{
    int64_t init_perm_data = init_permutate(data);    // perform initial permutation

    // divide on blocks by 32 bits
    int32_t left_data = (init_perm_data & left_mask) >> 32; // needs extra shifting to reduce size to 32 bits
    int32_t right_data = init_perm_data & right_mask;

    int64_t final_perm_data = final_permutate(data);
    
    return final_perm_data;
};