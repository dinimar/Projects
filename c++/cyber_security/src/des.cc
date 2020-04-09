#include "des.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

const std::vector<uint8_t> DES::ip_table =
    {58, 50, 42, 34, 26, 18, 10, 2,
     60, 52, 44, 36, 28, 20, 12, 4,
     62, 54, 46, 38, 30, 22, 14, 6,
     64, 56, 48, 40, 32, 24, 16, 8,
     57, 49, 41, 33, 25, 17, 9, 1,
     59, 51, 43, 35, 27, 19, 11, 3,
     61, 53, 45, 37, 29, 21, 13, 5,
     63, 55, 47, 39, 31, 23, 15, 7};

const std::vector<uint8_t> DES::ps_1_key_table =
    {
        57, 49, 41, 33, 25, 17, 9, 1,
        58, 50, 42, 34, 26, 18, 10, 2,
        59, 51, 43, 35, 27, 19, 11, 3,
        60, 52, 44, 36, 63, 55, 47, 39,
        31, 23, 15, 7, 62, 54, 46, 38,
        30, 22, 14, 6, 61, 53, 45, 37,
        29, 21, 13, 5, 28, 20, 12, 4};

const std::vector<uint8_t> DES::pc_2_key_table =
    {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32};

const std::vector<uint8_t> DES::r_block_table =
    {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
     8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
     16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
     24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

// 8 S-boxes with 4x16 table
const std::vector<std::vector<std::vector<uint8_t>>> DES::s_box_table = {{// S_1
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

const std::vector<uint8_t> DES::p_table{
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25};

const std::vector<uint8_t> DES::ip_inv_table =
    {40, 8, 48, 16, 56, 24, 64, 32,
     39, 7, 47, 15, 55, 23, 63, 31,
     38, 6, 46, 14, 54, 22, 62, 30,
     37, 5, 45, 13, 53, 21, 61, 29,
     36, 4, 44, 12, 52, 20, 60, 28,
     35, 3, 43, 11, 51, 19, 59, 27,
     34, 2, 42, 10, 50, 18, 58, 26,
     33, 1, 41, 9, 49, 17, 57, 25};

const std::map<std::string, uint64_t> DES::key_masks{
    {"left", 0xFFFFFFFFF0000000}, // 28 left bits
    {"right", 0xFFFFFFF}          // 28 right bits
};

const std::map<std::string, uint64_t> DES::data_masks{
    {"right", 0xFFFFFFFF},       // 32 right bits
    {"left", 0xFFFFFFFF00000000} // 32 left bits
};

uint64_t DES::extract_block6(const uint8_t n, const uint64_t &data)
{
    // shift block to the left, multiply on 0x3F to remove unnecessary bits
    return ((data >> (6 * (7 - n))) & 0x3F); // 0x3F = 0b111111 - 6 bits
}

uint64_t DES::s_box(const uint8_t n, const uint64_t block)
{
    // value accessed by block number and masking on passing block
    int8_t row = (get_nth_bit(0, 6, block) << 1) + get_nth_bit(5, 6, block);
    int8_t col = (block & 0x1E) >> 1;

    return (DES::s_box_table[n][row][col]);
}

int32_t DES::rotl32(int32_t data, size_t cycle, size_t shifts)
{
    for (size_t i = 0; i < shifts; i++)
    {
        data = data << 1;                        // shift to the left
        data += get_nth_bit(0, cycle + 1, data); // add shifted out bit to the begin
    }

    return data & key_masks.at("right"); // remove bits after 28th
}

uint64_t DES::get_nth_bit(const uint8_t &n, const uint8_t &size, const uint64_t &data)
{
    return ((data >> (size - n - 1)) & 1); // shift bits and mask
}

int64_t DES::permutate(const uint64_t &data, const uint8_t &size, const std::vector<uint8_t> &table)
{
    int64_t perm_data = 0; // zero-initialized permutated data

    for (size_t i = 0; i < table.size(); i++)
    {
        // bit shifting by 0, 1 till 63 bits,
        // a value need decrease by 1 to get index
        perm_data += (get_nth_bit(table[i] - 1, size, data) << table.size() - i - 1);
    }

    return perm_data;
}

uint64_t DES::reverse_permutate(const uint64_t &data, const uint8_t &size, const std::vector<uint8_t> &table)
{
    int64_t unperm_data = 0; // zero-initialized unpermutated data

    for (size_t i = 0; i < table.size(); i++)
    {
        // bit shifting by 0, 1 till 63 bits,
        // a value need decrease by 1 to get index
        unperm_data += (get_nth_bit(i, size, data) << table.size() - table[i]);
    }

    return unperm_data;
}

void DES::s_func(uint64_t &right_block)
{
    int64_t tmp_left = 0;

    for (size_t i = 0; i < 8; i++)
    {
        tmp_left += (DES::s_box(i, DES::extract_block6(i, right_block)) << ((8 - i - 1) * 4));
    }

    right_block = tmp_left;
}

int64_t DES::bitwise_sum(int64_t summand1, int64_t summand2)
{
    return summand1 ^ summand2;
}

int64_t DES::round_key(const int &round_num)
{
    int8_t shift_num = 2;  // number of shifting
    int64_t round_key = 0; // 48-bit round key

    if (round_num == 0 || round_num == 1 || round_num == 8 || round_num == 15)
        shift_num = 1;

    if (round_num == 0)
        key_ = permutate(key_, 64, DES::ps_1_key_table); // PS-1 permutation, 56-bit key in result

    std::map<std::string, uint64_t> key_blocks = divide(key_, key_masks, 28); // divide by 28-bit blocks

    key_blocks["left"] = rotl32(key_blocks["left"], 28, shift_num);
    key_blocks["right"] = rotl32(key_blocks["right"], 28, shift_num);

    key_ = restore_data(key_blocks, 28); // restore & update key

    return permutate(key_, 56, pc_2_key_table);
}

std::map<std::string, uint64_t> DES::divide(const uint64_t &data, const std::map<std::string, uint64_t> &masks, const uint8_t &mask_length)
{
    std::map<std::string, uint64_t> data_parts; // result vectors

    // left bits
    data_parts["left"] = data & masks.at("left");
    data_parts["left"] = data_parts["left"] >> mask_length; // extra shifting for removing zero bits
    // right bits
    data_parts["right"] = data & masks.at("right");

    return data_parts;
}

int64_t DES::restore_data(std::map<std::string, uint64_t> data_parts, int block_size)
{
    uint64_t data = data_parts["left"] << block_size;
    data += data_parts["right"];

    return data;
}

void DES::round_encrypt(std::map<std::string, uint64_t> &blocks, int round_num)
{
    uint64_t res = permutate(blocks["right"], 32, r_block_table); // result of e_function
    res = bitwise_sum(res, round_keys[round_num]);                // bitwise sum with round key
    s_func(res);                                                  // result of s_function
    res = permutate(res, 32, p_table);                            // result of p_function

    blocks["left"] = bitwise_sum(blocks["left"], res); // bitwise sum of L and R, update L
    std::swap(blocks["left"], blocks["right"]);        // swap values
}

void DES::round_decrypt(std::map<std::string, uint64_t> &blocks, int round_num)
{
    uint64_t res = permutate(blocks["left"], 32, r_block_table); // result of e_function
    res = bitwise_sum(res, round_keys[round_num]);               // bitwise sum with round key
    s_func(res);                                                 // result of s_function
    res = permutate(res, 32, p_table);                           // result of p_function

    blocks["right"] = bitwise_sum(blocks["right"], res); // bitwise sum of R(new) and res(R_old_modified), update R (inverse operation)
    std::swap(blocks["left"], blocks["right"]);          // swap values
}

uint64_t DES::encrypt(uint64_t data)
{
    data = permutate(data, 64, ip_table);        // initial permutation
    data_blocks_ = divide(data, data_masks, 32); // divide on L, R blocks

    // 16 encryption rounds
    for (size_t i = 0; i < 16; i++)
        round_encrypt(data_blocks_, i);

    std::swap(data_blocks_["left"], data_blocks_["right"]); // reverse blocks
    uint64_t enc_data = restore_data(data_blocks_, 32);      // restore data from blocks

    return permutate(enc_data, 64, ip_inv_table); // final permutation
}

uint64_t DES::decrypt(uint64_t enc_data)
{
    enc_data = reverse_permutate(enc_data, 64, ip_inv_table); // inverse final permutation

    data_blocks_ = divide(enc_data, data_masks, 32);        // divide data on blocks (inverse of restore_data())
    std::swap(data_blocks_["left"], data_blocks_["right"]); // inverse reverse blocks

    // 16 decryption rounds
    for (int i = 15; i >= 0; i--)
        round_decrypt(data_blocks_, i);

    uint64_t raw_data = restore_data(data_blocks_, 32); // restore one block of data (inverse of divide())

    return reverse_permutate(raw_data, 64, ip_table);
}

void DES::encryptN(std::vector<uint64_t> & raw_vector)
{
    for (uint64_t & block: raw_vector)
        block = encrypt(block);
}

void DES::decryptN(std::vector<uint64_t> & enc_vector)
{
    for (uint64_t & block: enc_vector)
        block = decrypt(block);
}