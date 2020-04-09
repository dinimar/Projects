#ifndef DES_H_
#define DES_H_
#include <map>
#include <string>
#include <array>
#include <vector>

class DES
{
private:
    uint64_t key_; // key for encryption/decryption using only last 7 bytes
    std::map<std::string, uint64_t> data_blocks_;

public:
    // Constructor
    // Initializes key for encryption/decryption
    DES(uint64_t key) : key_(key)
    {
        // initialize all round keys
        for (size_t i = 0; i < 16; i++)
        {
            round_keys.push_back(round_key(i));
        }
    };

    DES(const DES &des) = default;
    DES(DES &&des) = default;
    DES &operator=(const DES &des) = default;
    DES &operator=(DES &&des) = default;
    virtual ~DES() = default;

    std::vector<uint64_t> round_keys; // keys for each of 16 round of encryption

    // https://en.wikipedia.org/wiki/DES_supplementary_material#Initial_permutation_(IP)
    static const std::vector<uint8_t> ip_table;
    static const std::vector<uint8_t> r_block_table;
    static const std::vector<uint8_t> ip_inv_table;
    // 8 S-boxes with 4x16 table
    static const std::vector<std::vector<std::vector<uint8_t>>> s_box_table;
    static const std::vector<uint8_t> p_table;

    static const std::map<std::string, uint64_t> key_masks;
    static const std::map<std::string, uint64_t> data_masks;
    static const std::vector<uint8_t> ps_1_key_table;
    static const std::vector<uint8_t> pc_2_key_table;

    // static const int32_t rotation_key_mask = 0b00001111111111111111111111111111; // 28-bit mask

    // returns nth (by index) bit of passed bit sequence
    static uint64_t get_nth_bit(const uint8_t & n, const uint8_t & size, const uint64_t & data);

    // returns nth 6-bit block (by index) of passed bit sequence
    // help function for S permutation
    static uint64_t extract_block6(const uint8_t n, const uint64_t & data);

    // transforms passed 6-bit block into 4-bit block from S box table
    // arguments: n - block number [0-8]; data - block
    static uint64_t s_box(const uint8_t n, const uint64_t data);

    // divides data by provided masks and their lenghts
    static std::map<std::string, uint64_t> divide(const uint64_t & data, const std::map<std::string, uint64_t> & masks, const uint8_t & mask_length);

    // restores 56-bit from 28-bit left & right parts
    static int64_t restore_data(std::map<std::string, uint64_t> data_blocks, int block_size);

    // rotates passed 32 bits cyclically to the left
    // n - passed number, cycle - number of bits for cycle
    // shifts - amount of shifts
    static int32_t rotl32(int32_t n, size_t cycle, size_t shifts);

    // generates round key (without shifting)
    // basing on passed key_
    // int64_t generate_round_key();
    static int64_t bitwise_sum(int64_t summand1, int64_t summand2);

    // updates left & right block via s_box permutation
    static void s_func(uint64_t & left_block);

    // permutation functions
    static int64_t permutate(const uint64_t & data, const uint8_t & size, const std::vector<uint8_t> & table);
    static uint64_t reverse_permutate(const uint64_t & data, const uint8_t & size, const std::vector<uint8_t> &table);

    // generates round key
    // round_num - rounder number [0..15]
    int64_t round_key(const int &round_num);

    // encrypts blocks for a round
    // blocks - map of right, left block, round_num - round number
    void round_encrypt(std::map<std::string, uint64_t> &blocks, int round_num);
    void round_decrypt(std::map<std::string, uint64_t> &blocks, int round_num);

    // encrypts passed data with previously defined key
    uint64_t encrypt(uint64_t data);
    // decrypts ecnrypted data with previously defined key
    uint64_t decrypt(uint64_t enc_data);
};

#endif