#ifndef DES_H_
#define DES_H_
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

    // https://en.wikipedia.org/wiki/DES_supplementary_material
    // permuatation tables, 64 bits for each
    std::vector<int> init_table =
        {58, 50, 42, 34, 26, 18, 10, 2,
         60, 52, 44, 36, 28, 20, 12, 4,
         62, 54, 46, 38, 30, 22, 14, 6,
         64, 56, 48, 40, 32, 24, 16, 8,
         57, 49, 41, 33, 25, 17, 9, 1,
         59, 51, 43, 35, 27, 19, 11, 3,
         61, 53, 45, 37, 29, 21, 13, 5,
         63, 55, 47, 39, 31, 23, 15, 7};

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

    std::array<std::array<std::array<int, 16>, 4>, 8>   // 8 S-boxes with 4x16 tables
        s_box_table = {
            // S_1
            {
                {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
            },
            // S_2
            {
                {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
            }};
    int64_t get_nth_bit(int n, int64_t data);

public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(int64_t key) : key_(key){};

    DES(const DES &des) = default;
    DES(DES &&des) = default;
    DES &operator=(const DES &des) = default;
    DES &operator=(DES &&des) = default;
    virtual ~DES() = default;

    // permutation functions
    int64_t permutate(int64_t data, std::vector<int> table);
    // int64_t final_permutate(int64_t data);

    int64_t e_func(int32_t data); // extends 32-bit data to 48-bit with permutations

    // encrypts passed data with previously defined key
    int64_t encrypt(int64_t data);
};

#endif