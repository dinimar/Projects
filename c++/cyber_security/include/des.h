#ifndef DES_H_
#define DES_H_
#include <string>
#include <array>

class DES
{
private:
    static const int BYTES_NUM = 7;
    static const int64_t left_mask = 0x1111111100000000;
    static const int64_t right_mask = 0x0000000011111111;

    int64_t key_; // key for encryption/decryption using only last 7 bytes

    // permuatation tables, 64 bits for each
    std::array<int, 64> init_table{
        {58, 50, 42, 34, 26, 18, 10, 2,
         60, 52, 44, 36, 28, 20, 12, 4,
         62, 54, 46, 38, 30, 22, 14, 6,
         64, 56, 48, 40, 32, 24, 16, 8,
         57, 49, 41, 33, 25, 17, 9, 1,
         59, 51, 43, 35, 27, 19, 11, 3,
         61, 53, 45, 37, 29, 21, 13, 5,
         63, 55, 47, 39, 31, 23, 15, 7}};

    std::array<int, 64> final_table{
        {40, 8, 48, 16, 56, 24, 64, 32,
         39, 7, 47, 15, 55, 23, 63, 31,
         38, 6, 46, 14, 54, 22, 62, 30,
         37, 5, 45, 13, 53, 21, 61, 29,
         36, 4, 44, 12, 52, 20, 60, 28,
         35, 3, 43, 11, 51, 19, 59, 27,
         34, 2, 42, 10, 50, 18, 58, 26,
         33, 1, 41, 9, 49, 17, 57, 25}};

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
    int64_t init_permutate(int64_t data);
    int64_t final_permutate(int64_t data);
    
    // Encrypt passed data with previously defined key
    int64_t encrypt(int64_t data);

};

#endif