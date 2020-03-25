#include "des.h"
#include <vector>
#include <iostream>

const std::vector<int> DES::ip_table = 
        {58, 50, 42, 34, 26, 18, 10, 2,
         60, 52, 44, 36, 28, 20, 12, 4,
         62, 54, 46, 38, 30, 22, 14, 6,
         64, 56, 48, 40, 32, 24, 16, 8,
         57, 49, 41, 33, 25, 17, 9, 1,
         59, 51, 43, 35, 27, 19, 11, 3,
         61, 53, 45, 37, 29, 21, 13, 5,
         63, 55, 47, 39, 31, 23, 15, 7};

int64_t DES::get_nth_bit(int n, int64_t data)
{
    return (data >> n) & 1; // shift bits and mask
}

int32_t DES::rotl32(int32_t n, unsigned int cycle, unsigned int shifts)
{
    for (size_t i = 0; i < shifts; i++)
    {
        n << 1;                     // shift to the left
        n += get_nth_bit(n, 29);    // add shifted out bit to the begin
    }

    return n & rotation_key_mask;   // remove bits after 28th
}

int64_t DES::permutate(int64_t data, std::vector<int> table)
{
    int64_t perm_data = 0;  // zero-initialized permutated data
    int k = 0;              // multiplier for bits

    for (int & a: table)
    {
        // bit shifting by 0, 1 till 63 bits, 
        // a value need decrease by 1 to get index
        perm_data += (get_nth_bit(a-1, data) << k);
        ++k;
    }

    return perm_data;
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
    int64_t init_perm_data = permutate(data, DES::ip_table);    // perform initial permutation

    // divide on blocks by 32 bits
    // int32_t left_data = (init_perm_data & left_mask) >> 32; // needs extra shifting to reduce size to 32 bits
    // int32_t right_data = init_perm_data & right_mask;

    // int64_t round_key = permutate(key_, p_key_table_);      // initial round key (no bit shifting)

    // 15 rounds of encryption
    // for(size_t i=0; i<15; ++i)
    // {
        // e_func
    //     int64_t out_data_left = permutate(left_data, r_block_table) // perform permutation 
    //                             ^ key_                              // XOR with key
    //                             << 16 >> 16;                         // remove first 16 bits that added after XOR
    // }
                        
    // int64_t out_data_right = permutate(right_data, r_block_table);

    // int64_t final_perm_data = permutate(data, final_table);
    
    return init_perm_data;
};

void bin(int64_t n) 
{ 
    /* step 1 */
    if (n > 1) 
        bin(n/2); 
  
    /* step 2 */
    std::cout << n % 2; 
} 

// int main()
// {
//     int64_t data = 0b101010;
//     int64_t ip_data = 0b010101;

//     std::vector<int> table {2, 1, 4, 3, 6, 5};

//     // std::cout << "Hello world!" << std::endl;

//     return 0;
//     // printf("%d", DES::permutate(data, table));
// //     bin(data);
// //     std::cout << std::endl;
// //   bin(DES::permutate(data, DES::ip_table));
// }