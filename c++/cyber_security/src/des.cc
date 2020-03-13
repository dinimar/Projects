#include "des.h"

int64_t DES::get_nth_bit(int n, int64_t data)
{
    return (data >> n) & 1; // shift bits and mask
}

int64_t DES::permutate(int64_t data, std::vector<int> table)
{
    int64_t perm_data = 0;  // zero-initialized permutated data
    int k = 0;              // multiplier for bits

    for (int & a: table)
    {
        perm_data += get_nth_bit(k, data) << a; // bit shifting by 0, 1 till 63 bits
        ++k;
    }
}

int64_t DES::generate_round_key()
{
    int64_t perm_data = 0;  // zero-initialized permutated data
    int k = 0;              // multiplier for bits

    for (int & a: p_key_table_)
    {
        perm_data += get_nth_bit(a, key_) << k; // bit shifting by 0, 1 till 63 bits
        ++k;
    }

    return perm_data;
}

// int64_t DES::final_permutate(int64_t data)
// {
//     int64_t perm_data = 0;  // zero-initialized permutated data
//     int k = 0;              // multiplier for bits

//     for (int & a: final_table)
//     {
//         perm_data += get_nth_bit(k, data) << a; // bit shifting by 0, 1 till 63 bits
//         ++k;
//     }
// }

// int64_t DES::e_func(int32_t data)
// {
//     int64_t perm_data = 0;  // zero-initialized permutated data
//     int k = 0;              // multiplier for bits

//     for (int & a: r_block_table)
//     {
//         perm_data += get_nth_bit(k, data) << a;
//         ++k;
//     }
// }

int64_t DES::encrypt(int64_t data)
{
    int64_t init_perm_data = permutate(data, init_table);    // perform initial permutation

    // divide on blocks by 32 bits
    int32_t left_data = (init_perm_data & left_mask) >> 32; // needs extra shifting to reduce size to 32 bits
    int32_t right_data = init_perm_data & right_mask;

    int64_t round_key = permutate(key_, p_key_table_);      // initial round key (no bit shifting)

    // 15 rounds of encryption
    for(size_t i=0; i<15; ++i)
    {
        // e_func
        int64_t out_data_left = permutate(left_data, r_block_table) // perform permutation 
                                ^ key_                              // XOR with key
                                << 16 >> 16;                         // remove first 16 bits that added after XOR
    }
                        
    int64_t out_data_right = permutate(right_data, r_block_table);

    int64_t final_perm_data = permutate(data, final_table);
    
    return final_perm_data;
};