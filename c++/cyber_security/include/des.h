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
    static const std::vector<int> ip_table;
    static const std::vector<int> r_block_table;
    // 8 S-boxes with 4x16 table
    static const std::vector<std::vector<std::vector<int8_t>>> s_box_table;    
    static const std::vector<int> p_table;
    
    static const std::map<std::string, int64_t> key_masks;
    static const std::map<std::string, int64_t> data_masks;
    static const std::vector<int> pc_1_key_table;
    static const std::vector<int> pc_2_key_table;


    static const int32_t rotation_key_mask = 0b00001111111111111111111111111111;    // 28-bit mask
    
    // returns nth (by index) bit of passed bit sequence
    static int64_t get_nth_bit(int n, int size, int64_t data);

    // returns nth 6-bit block (by index) of passed bit sequence
    // help function for S permutation
    static int64_t extract_block6(int n, const int64_t & data);

    // transforms passed 6-bit block into 4-bit block from S box table
    // arguments: n - block number [0-8]; data - block
    static int64_t s_box(int n, int64_t data);

    // divides data by provided masks and their lenghts
    static std::map<std::string, uint64_t> divide(int64_t data, std::map<std::string, int64_t> masks, int mask_length); 

    // restores 56-bit from 28-bit left & right parts
    static int64_t restore_key(std::map<std::string, uint64_t> key_parts);

    // rotates passed 32 bits cyclically to the left
    // n - passed number, cycle - number of bits for cycle
    // shifts - amount of shifts
    static int32_t rotl32(int32_t n, unsigned int cycle, unsigned int shifts);

    // generates round key (without shifting)
    // basing on passed key_
    // int64_t generate_round_key();
    static int64_t bitwise_sum(int64_t summand1, int64_t summand2);

    // updates left & right block via s_box permutation
    static void s_func(int64_t & left_block);

    // permutation functions
    static int64_t permutate(int64_t data, int size, const std::vector<int> & table);

    // int64_t e_func(int32_t data); // extends 32-bit data to 48-bit with permutations

    // encrypts passed data with previously defined key
    int64_t encrypt(int64_t data);
};

#endif