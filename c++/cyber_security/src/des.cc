#include "des.h"
#include <vector>
#include <map>
#include <string>
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

const std::vector<int> DES::pc_1_key_table =
      {
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4};

const std::vector<int> DES::pc_2_key_table =
    {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32};

const std::vector<int> DES::r_block_table =
    {32, 1, 2, 3, 4, 5,
     4, 5, 6, 7, 8, 9,
     8, 9, 10, 11, 12, 13,
     12, 13, 14, 15, 16, 17,
     16, 17, 18, 19, 20, 21,
     20, 21, 22, 23, 24, 25,
     24, 25, 26, 27, 28, 29,
     28, 29, 30, 31, 32, 1};

const std::map<std::string, int64_t> DES::key_masks{
    {"left", 0xFFFFFFF},            // 28 left bits 
    {"right", 0xFFFFFFFFF0000000}   // 28 right bits
};

const std::map<std::string, int64_t> DES::data_masks {
    {"left", 0xFFFFFFFF},           // 32 left bits
    {"right", 0xFFFFFFFF00000000}   // 32 right bits
};

int64_t DES::get_nth_bit(int n, int64_t data)
{
    return (data >> n) & 1; // shift bits and mask
}

int32_t DES::rotl32(int32_t n, unsigned int cycle, unsigned int shifts)
{
    for (size_t i = 0; i < shifts; i++)
    {
        n << 1;                  // shift to the left
        n += get_nth_bit(n, 29); // add shifted out bit to the begin
    }

    return n & rotation_key_mask; // remove bits after 28th
}

int64_t DES::permutate(int64_t data, std::vector<int> table)
{
    int64_t perm_data = 0; // zero-initialized permutated data
    int k = 0;             // multiplier for bits

    for (int &a : table)
    {
        // bit shifting by 0, 1 till 63 bits,
        // a value need decrease by 1 to get index
        perm_data += (get_nth_bit(a - 1, data) << k);
        ++k;
    }

    return perm_data;
}

// int64_t DES::generate_round_key()
// {
//     int64_t perm_data = 0; // zero-initialized permutated data
//     int k = 0;             // multiplier for bits

//     for (int &a : p_key_table_)
//     {
//         perm_data += get_nth_bit(a, key_) << k; // bit shifting by 0, 1 till 63 bits
//         ++k;
//     }

//     return perm_data;
// }

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

std::map<std::string, uint64_t> DES::divide(int64_t data, std::map<std::string, int64_t> masks, int mask_length)
{
    std::map<std::string, uint64_t> data_parts; // result vectors

    // left bits
    data_parts["left"] = data & masks["left"];            
    // right bits, extra shifting for removing zero bits
    data_parts["right"] = data & masks["right"];
    data_parts["right"] = data_parts["right"] >> mask_length;

    return data_parts;
}

int64_t DES::restore_key(std::map<std::string, uint64_t> key_parts)
{
    int64_t key = key_parts["right"];

    key += (key_parts["left"] << 28);

    return key;
}

int64_t DES::encrypt(int64_t data)
{
    int64_t init_perm_data = permutate(data, DES::ip_table); // perform initial permutation
    std::map<std::string, uint64_t> data_parts = DES::divide(init_perm_data, DES::data_masks, 32);
    // divide on blocks by 32 bits
    // int32_t left_data = (init_perm_data & left_mask) >> 32; // needs extra shifting to reduce size to 32 bits
    // int32_t right_data = init_perm_data & right_mask;

    // int64_t round_key = permutate(key_, p_key_table_);      // initial round key (no bit shifting)

    int64_t iter_key = permutate(key_, DES::pc_1_key_table);  // PC-1 permutation
    // 15 rounds of encryption
    for (size_t i = 0; i < 15; ++i)
    {
        // R block permutation
        data_parts["left"] = DES::permutate(data_parts["left"], DES::r_block_table);
        data_parts["right"] = DES::permutate(data_parts["right"], DES::r_block_table);

        // Key generation
        std::map<std::string, uint64_t> key_parts = DES::divide(iter_key, DES::key_masks, 28);

        if ((i >= 1 & i <= 7) || (i >= 9 && i <= 14))
        {
            key_parts["left"] = rotl32(key_parts["left"], 28, 2);
            key_parts["right"] = rotl32(key_parts["right"], 28, 2);
        }
        else
        {
            key_parts["left"] = rotl32(key_parts["left"], 28, 1);
            key_parts["right"] = rotl32(key_parts["right"], 28, 1);
        }

        iter_key = DES::restore_key(key_parts);         // 56-bit restored from 28-bit parts
        int64_t round_key = permutate(iter_key, DES::pc_2_key_table);

        // E function
        data_parts["left"] ^= round_key;
        data_parts["right"] ^= round_key;
    }

    // int64_t out_data_right = permutate(right_data, r_block_table);

    // int64_t final_perm_data = permutate(data, final_table);

    return init_perm_data;
};

void bin(int64_t n)
{
    /* step 1 */
    if (n > 1)
        bin(n / 2);

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