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

// 8 S-boxes with 4x16 table
const std::vector<std::vector<std::vector<int8_t>>> DES::s_box_table = {{                                
    // S_1
    {{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}}},
    // S_2
    {{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}}},
    // S_3
    {{
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
    }},
    // S_4
    {{
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
    }},
    // S_5
    {{
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
    }},
    // S_6
    {{
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
    }},
    // S_7
    {{
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
    }},
    // S_8
    {{
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
    }}}};

const std::vector<int> DES::p_table {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

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

int64_t DES::extract_block6(int n, int64_t data)
{
    return (data >> (6 * n)) & 0x3F;    // 0x2F = 0b111111 - 6 bits
}

int64_t DES::s_box(int n, int64_t block)
{
    // value accessed by block number and masking on passing block
    return DES::s_box_table[n][block & 0x21][block & 0x1E];
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

        // S-permutation
        int64_t tmp_left = 0;
        int64_t tmp_right = 0;
        for(size_t i=0; i<6; i++)
        {
            tmp_left += (DES::s_box(i, DES::extract_block6(i, data_parts["left"])) << i*4);
            tmp_right += (DES::s_box(i, DES::extract_block6(i, data_parts["right"])) << i*4);  
        }
        data_parts["left"] = tmp_left;
        data_parts["right"] = tmp_right;

        // P-permutation
        data_parts["left"] = DES::permutate(data_parts["left"], DES::p_table);
        data_parts["right"] = DES::permutate(data_parts["right"], DES::p_table);
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