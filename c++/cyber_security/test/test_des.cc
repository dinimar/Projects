#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include <map>
#include <string>
#include "des.h"

BOOST_AUTO_TEST_CASE(des_nth_bit)
{
  int64_t a = 2;
  int64_t b = 0x1;

  BOOST_CHECK_EQUAL(1, DES::get_nth_bit(0, 2, a));
  BOOST_CHECK_EQUAL(0, DES::get_nth_bit(1, 2, a));
  BOOST_CHECK_EQUAL(1, DES::get_nth_bit(0, 1, b));
}

BOOST_AUTO_TEST_CASE(des_permutation)
{
  int64_t data = 0x123456ABCD132536;    // raw data
  int64_t ip_data = 0x14A7D67818CA18AD; // data after initial permutation

  BOOST_CHECK_BITWISE_EQUAL(ip_data, DES::permutate(data, 64, DES::ip_table));
}

BOOST_AUTO_TEST_CASE(des_rotl32)
{
  int32_t rotation_key_mask = 0b00001111111111111111111111111111;

  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 0));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 1));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 14));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 28));
}

BOOST_AUTO_TEST_CASE(des_divide_key)
{
  int64_t key = 0x00FFFFFFFFFFFFFF; // raw key

  std::map<std::string, uint64_t> key_parts = DES::divide(key, DES::key_masks, 28);

  BOOST_CHECK_BITWISE_EQUAL(key_parts["left"], key_parts["right"]);
}

BOOST_AUTO_TEST_CASE(des_divide_data)
{
  int64_t key = 0xFFFFFFFFFFFFFFFF; // raw data

  std::map<std::string, uint64_t> data_parts = DES::divide(key, DES::data_masks, 32);

  BOOST_CHECK_BITWISE_EQUAL(data_parts["left"], data_parts["right"]);
}

BOOST_AUTO_TEST_CASE(des_restore_key)
{
  std::map<std::string, uint64_t> key_parts;
  key_parts["left"] = 0x0FFFFFFF;
  key_parts["right"] = 0x0FFFFFFF;

  int64_t rest_key = DES::restore_key(key_parts);

  BOOST_CHECK_BITWISE_EQUAL(0x00FFFFFFFFFFFFFF, rest_key);
}

BOOST_AUTO_TEST_CASE(des_permutate_r_block)
{
  int64_t part_data = 0xF0AAF0AA;
  int64_t exp_res = 0xA15557A1555;

  int64_t perm_data = DES::permutate(part_data, 32, DES::r_block_table);
}

BOOST_AUTO_TEST_CASE(des_bitwise_sum)
{
  int64_t e_data = 0x7A15557A1555; // data returned by e function
  int64_t key = 0x1B02EFFC7072;

  int64_t left_block = 0xCC00CCFF;
  int64_t right_block = 0x234AA9BB;

  BOOST_CHECK_BITWISE_EQUAL(0x6117BA866527, DES::bitwise_sum(e_data, key));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xEF4A6544, DES::bitwise_sum(left_block, right_block));
}

BOOST_AUTO_TEST_CASE(des_extract_block6)
{
  int64_t data_48bit = 0x0000FFFFFFFFFFFF;

  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(0, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(1, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(2, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(3, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(4, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(5, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(6, data_48bit));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(7, data_48bit));

  int64_t b = 0x7F;

  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x1, DES::extract_block6(6, b));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3F, DES::extract_block6(7, b));

  int64_t a = 0x12;          // 18
  a += ((int64_t)0x11 << 6); // 17
  a += ((int64_t)0x3 << 12); // 3
  a += ((int64_t)0x2 << 18); // 2
  a += ((int64_t)0x1 << 24); // 1
  a += ((int64_t)0xD << 30); // 13
  a += ((int64_t)0xC << 36); // 12
  a += ((int64_t)0xB << 42); // 11

  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xB, DES::extract_block6(0, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC, DES::extract_block6(1, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD, DES::extract_block6(2, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x1, DES::extract_block6(3, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x2, DES::extract_block6(4, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3, DES::extract_block6(5, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x11, DES::extract_block6(6, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x12, DES::extract_block6(7, a));
}

BOOST_AUTO_TEST_CASE(des_s_box)
{
  int64_t a = 0x7F;
  int64_t block_6 = DES::extract_block6(6, a);

  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x0, DES::s_box(0, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x3, DES::s_box(1, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD, DES::s_box(2, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD, DES::s_box(3, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xE, DES::s_box(4, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xA, DES::s_box(5, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD, DES::s_box(6, block_6));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x1, DES::s_box(7, block_6));
}

BOOST_AUTO_TEST_CASE(des_s_func)
{
  int64_t a = 0x12;          // 18
  a += ((int64_t)0x11 << 6); // 17
  a += ((int64_t)0x3 << 12); // 3
  a += ((int64_t)0x2 << 18); // 2
  a += ((int64_t)0x1 << 24); // 1
  a += ((int64_t)0xD << 30); // 13
  a += ((int64_t)0xC << 36); // 12
  a += ((int64_t)0xB << 42); // 11

  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xB, DES::extract_block6(0, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC, DES::extract_block6(1, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD, DES::extract_block6(2, a));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x1, DES::extract_block6(3, a));

  int64_t exp_res = DES::s_box_table[7][0][9];     // S_8[0][9]
  exp_res += (DES::s_box_table[6][1][8] << 4);     // S_7[1][8]
  exp_res += (DES::s_box_table[5][1][1] << 4 * 2); // S_6[1][1]
  exp_res += (DES::s_box_table[4][0][1] << 4 * 3); // S_5[0][1]
  exp_res += (DES::s_box_table[3][1][0] << 4 * 4); // S_4[1][0]
  exp_res += (DES::s_box_table[2][1][6] << 4 * 5); // S_3[1][6]
  exp_res += (DES::s_box_table[1][0][6] << 4 * 6); // S_2[0][5]
  exp_res += (DES::s_box_table[0][1][5] << 4 * 7); // S_1[1][5]

  DES::s_func(a);

  BOOST_CHECK_BITWISE_EQUAL(exp_res, a);
}

BOOST_AUTO_TEST_CASE(des_perm)
{
  std::vector<int> table = {2, 4, 1, 4};
  int64_t data = 0x5;

  int64_t perm_data = DES::permutate(data, 4, table);

  BOOST_CHECK_BITWISE_EQUAL(perm_data, (int64_t)0xD);
}

BOOST_AUTO_TEST_CASE(des_P_permutation)
{
  int64_t data = DES::s_box_table[7][0][9];     // S_8[0][9]
  data += (DES::s_box_table[6][1][8] << 4);     // S_7[1][8]
  data += (DES::s_box_table[5][1][1] << 4 * 2); // S_6[1][1]
  data += (DES::s_box_table[4][0][1] << 4 * 3); // S_5[0][1]
  data += (DES::s_box_table[3][1][0] << 4 * 4); // S_4[1][0]
  data += (DES::s_box_table[2][1][6] << 4 * 5); // S_3[1][6]
  data += (DES::s_box_table[1][0][6] << 4 * 6); // S_2[0][5]
  data += (DES::s_box_table[0][1][5] << 4 * 7); // S_1[1][5]

  int64_t perm_data = DES::permutate(data, 32, DES::p_table);

  for (size_t i = 0; i < 32; i++)
  {
    BOOST_CHECK_EQUAL(DES::get_nth_bit(DES::p_table[i] - 1, 32, data),
                      DES::get_nth_bit(i, 32, perm_data));
  }
}

BOOST_AUTO_TEST_CASE(des_P_S_permutations)
{
  int64_t left_block, right_block = 0x6117BA866527;
  DES::s_func(right_block);

  right_block = DES::permutate(right_block, 32, DES::p_table);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x234AA9BB, right_block);
}

// BOOST_AUTO_TEST_CASE( des_encrypt )
// {
//   int64_t key = 0x0101010101010101;
//   int64_t data = 0x95F8A5E5DD31D900;

//   DES des(key);  // initialize object

//   BOOST_CHECK_BITWISE_EQUAL(0x8000000000000000, des.encrypt(data));
// }
