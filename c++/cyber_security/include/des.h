#ifndef DES_H_
#define DES_H_
#include <map>
#include <string>
#include <array>
#include <vector>

class DES
{
private:
    static const int BYTES_NUM = 7;
    static const int64_t left_mask = 0x1111111100000000;
    static const int64_t right_mask = 0x0000000011111111;

    int64_t key_; // key for encryption/decryption using only last 7 bytes

    std::vector<int> final_table =
        {40, 8, 48, 16, 56, 24, 64, 32,
         39, 7, 47, 15, 55, 23, 63, 31,
         38, 6, 46, 14, 54, 22, 62, 30,
         37, 5, 45, 13, 53, 21, 61, 29,
         36, 4, 44, 12, 52, 20, 60, 28,
         35, 3, 43, 11, 51, 19, 59, 27,
         34, 2, 42, 10, 50, 18, 58, 26,
         33, 1, 41, 9, 49, 17, 57, 25};

    std::vector<int> r_block_table =
        {32, 1, 2, 3, 4, 5,
         4, 5, 6, 7, 8, 9,
         8, 9, 10, 11, 12, 13,
         12, 13, 14, 15, 16, 17,
         16, 17, 18, 19, 20, 21,
         20, 21, 22, 23, 24, 25,
         24, 25, 26, 27, 28, 29,
         28, 29, 30, 31, 32, 1};

    std::vector<std::vector<std::vector<int8_t>>> // 8 S-boxes with 4x16 table
        s_box_table = {{                          
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


public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(int64_t key) : key_(key){};

    DES(const DES &des) = default;
    DES(DES &&des) = default;
    DES &operator=(const DES &des) = default;
    DES &operator=(DES &&des) = default;
    virtual ~DES() = default;

    // https://en.wikipedia.org/wiki/DES_supplementary_material#Initial_permutation_(IP)
    // initial permuatation table
    static const std::vector<int> ip_table;

    static const std::map<std::string, int64_t> key_masks;
    static const std::map<std::string, int64_t> data_masks;
    static const std::vector<int> pc_1_key_table;
    static const std::vector<int> pc_2_key_table;


    static const int32_t rotation_key_mask = 0b00001111111111111111111111111111;    // 28-bit mask
    
    // returns nth (by index) bit of passed bit sequence
    static int64_t get_nth_bit(int n, int64_t data);

    // divides data by provided masks and their lenghts
    static std::map<std::string, uint32_t> divide(int64_t data, std::map<std::string, int64_t> masks, int mask_length); 

    // restores 56-bit from 28-bit left & right parts
    static int64_t restore_key(std::map<std::string, uint32_t> key_parts);

    // rotates passed 32 bits cyclically to the left
    // n - passed number, cycle - number of bits for cycle
    // shifts - amount of shifts
    static int32_t rotl32(int32_t n, unsigned int cycle, unsigned int shifts);

    // generates round key (without shifting)
    // basing on passed key_
    // int64_t generate_round_key();

    // permutation functions
    static int64_t permutate(int64_t data, std::vector<int> table);

    int64_t e_func(int32_t data); // extends 32-bit data to 48-bit with permutations

    // encrypts passed data with previously defined key
    int64_t encrypt(int64_t data);
};

#endif