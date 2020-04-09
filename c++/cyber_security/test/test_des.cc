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
  int32_t rotation_key_mask = 0xAAAAAAA;

  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 0));
  BOOST_CHECK_BITWISE_EQUAL((int32_t)0x5555555, DES::rotl32(rotation_key_mask, 28, 1));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 2));
  BOOST_CHECK_BITWISE_EQUAL((int32_t)0x5555555, DES::rotl32(rotation_key_mask, 28, 3));
}

BOOST_AUTO_TEST_CASE(des_divide_key)
{
  int64_t key = 0x00FFFFFFFFFFFFFF; // raw key

  std::map<std::string, uint64_t> key_parts = DES::divide(key, DES::key_masks, 28);

  BOOST_CHECK_BITWISE_EQUAL(key_parts["left"], key_parts["right"]);
}

BOOST_AUTO_TEST_CASE(des_divide_data)
{
  int64_t key = 0x00F0000FF0505005; // raw data

  std::map<std::string, uint64_t> data_parts = DES::divide(key, DES::key_masks, 28);

  BOOST_CHECK_BITWISE_EQUAL(data_parts["left"], (int64_t)0xF0000FF);
  BOOST_CHECK_BITWISE_EQUAL(data_parts["right"], (int64_t)0x0505005);
}

BOOST_AUTO_TEST_CASE(des_restore_key)
{
  std::map<std::string, uint64_t> key_parts;
  key_parts["left"] = 0x0FFFFFFF;
  key_parts["right"] = 0x0FFFFFFF;

  int64_t rest_key = DES::restore_data(key_parts, 28);

  BOOST_CHECK_BITWISE_EQUAL(0x00FFFFFFFFFFFFFF, rest_key);

  std::map<std::string, uint64_t> data_parts = {
      {"left", (int64_t)0x0A4CD995},
      {"right", (int64_t)0x43423234}};

  int64_t rest_data = DES::restore_data(data_parts, 32);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x0A4CD99543423234, rest_data);
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
  uint64_t a = 0x12;          // 18
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
  std::vector<uint8_t> table = {2, 4, 1, 4};
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
  uint64_t left_block, right_block = 0x6117BA866527;
  DES::s_func(right_block);

  right_block = DES::permutate(right_block, 32, DES::p_table);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x234AA9BB, right_block);
}

BOOST_AUTO_TEST_CASE(des_round_key)
{
  DES des(0x133457799BBCDFF1);

  BOOST_CHECK_BITWISE_EQUAL(0x1B02EFFC7072, des.round_keys[0]);
  BOOST_CHECK_BITWISE_EQUAL(0x79AED9DBC9E5, des.round_keys[1]);
  BOOST_CHECK_BITWISE_EQUAL(0x55FC8A42CF99, des.round_keys[2]);
  BOOST_CHECK_BITWISE_EQUAL(0x72ADD6DB351D, des.round_keys[3]);
  BOOST_CHECK_BITWISE_EQUAL(0x7CEC07EB53A8, des.round_keys[4]);
  BOOST_CHECK_BITWISE_EQUAL(0x63A53E507B2F, des.round_keys[5]);
  BOOST_CHECK_BITWISE_EQUAL(0xEC84B7F618BC, des.round_keys[6]);
  BOOST_CHECK_BITWISE_EQUAL(0xF78A3AC13BFB, des.round_keys[7]);
  BOOST_CHECK_BITWISE_EQUAL(0xE0DBEBEDE781, des.round_keys[8]);
  BOOST_CHECK_BITWISE_EQUAL(0xB1F347BA464F, des.round_keys[9]);
  BOOST_CHECK_BITWISE_EQUAL(0x215FD3DED386, des.round_keys[10]);
  BOOST_CHECK_BITWISE_EQUAL(0x7571F59467E9, des.round_keys[11]);
  BOOST_CHECK_BITWISE_EQUAL(0x97C5D1FABA41, des.round_keys[12]);
  BOOST_CHECK_BITWISE_EQUAL(0x5F43B7F2E73A, des.round_keys[13]);
  BOOST_CHECK_BITWISE_EQUAL(0xBF918D3D3F0A, des.round_keys[14]);
  BOOST_CHECK_BITWISE_EQUAL(0xCB3D8B0E17F5, des.round_keys[15]);
}

BOOST_AUTO_TEST_CASE(des_round_encrypt)
{
  int64_t key = 0x133457799BBCDFF1;
  int64_t data = 0x123456789ABCDEF;
  std::map<std::string, uint64_t> blocks = {{"left", 0xCC00CCFF}, {"right", 0xF0AAF0AA}};

  DES des(key); // initialize object

  des.round_encrypt(blocks, 0);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xF0AAF0AA, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xEF4A6544, blocks["right"]);

  des.round_encrypt(blocks, 1);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xEF4A6544, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xCC017709, blocks["right"]);

  des.round_encrypt(blocks, 2);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xCC017709, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xA25C0BF4, blocks["right"]);

  des.round_encrypt(blocks, 3);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xA25C0BF4, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x77220045, blocks["right"]);

  des.round_encrypt(blocks, 4);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x77220045, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x8A4FA637, blocks["right"]);

  des.round_encrypt(blocks, 5);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x8A4FA637, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xE967CD69, blocks["right"]);

  des.round_encrypt(blocks, 6);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xE967CD69, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x064ABA10, blocks["right"]);

  des.round_encrypt(blocks, 7);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x064ABA10, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD5694B90, blocks["right"]);

  des.round_encrypt(blocks, 8);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xD5694B90, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x247CC67A, blocks["right"]);

  des.round_encrypt(blocks, 9);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x247CC67A, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xB7D5D7B2, blocks["right"]);

  des.round_encrypt(blocks, 10);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xB7D5D7B2, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC5783C78, blocks["right"]);

  des.round_encrypt(blocks, 11);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC5783C78, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x75BD1858, blocks["right"]);

  des.round_encrypt(blocks, 12);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x75BD1858, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x18C3155A, blocks["right"]);

  des.round_encrypt(blocks, 13);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x18C3155A, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC28C960D, blocks["right"]);

  des.round_encrypt(blocks, 14);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xC28C960D, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x43423234, blocks["right"]);

  des.round_encrypt(blocks, 15);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x43423234, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x0A4CD995, blocks["right"]);
}

BOOST_AUTO_TEST_CASE(des_encrypt)
{
  int64_t key = 0x133457799BBCDFF1;
  int64_t data = 0x123456789ABCDEF;

  DES des(key); // initialize object

  int64_t res = des.encrypt(data);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x85E813540F0AB405, res);

  DES des_vector_key(0x0101010101010101);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x8000000000000000, des_vector_key.encrypt(0x95F8A5E5DD31D900));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x4000000000000000, des_vector_key.encrypt(0xDD7F121CA5015619));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x2000000000000000, des_vector_key.encrypt(0x2E8653104F3834EA));
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0x1000000000000000, des_vector_key.encrypt(0x4BD388FF6CD81D4F));
}

BOOST_AUTO_TEST_CASE(des_reverse_permutate)
{
  // fairy-tail example
  uint64_t un_data = 0x9A;
  std::vector<uint8_t> t_table = {1, 2, 7, 5, 4, 6, 8, 3};
  uint64_t t_data = DES::permutate(un_data, 8, t_table);
  BOOST_CHECK_BITWISE_EQUAL(un_data, DES::reverse_permutate(t_data, 8, t_table));

  // real-world example
  uint64_t perm_data = 0x85E813540F0AB405;
  BOOST_CHECK_BITWISE_EQUAL(0x0A4CD99543423234, DES::reverse_permutate(perm_data, 64, DES::ip_inv_table));
}

BOOST_AUTO_TEST_CASE(des_round_decrypt)
{
  int64_t key = 0x133457799BBCDFF1;
  DES des(key);

  std::map<std::string, uint64_t> blocks = {
      {"left", 0x43423234},
      {"right", 0x0A4CD995}};

  des.round_decrypt(blocks, 15);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xC28C960D, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x43423234, blocks["right"]);

  des.round_decrypt(blocks, 14);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x18C3155A, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xC28C960D, blocks["right"]);

  des.round_decrypt(blocks, 13);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x75BD1858, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x18C3155A, blocks["right"]);

  des.round_decrypt(blocks, 12);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xC5783C78, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x75BD1858, blocks["right"]);

  des.round_decrypt(blocks, 11);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xB7D5D7B2, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xC5783C78, blocks["right"]);

  des.round_decrypt(blocks, 10);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x247CC67A, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xB7D5D7B2, blocks["right"]);

  des.round_decrypt(blocks, 9);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xD5694B90, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x247CC67A, blocks["right"]);

  des.round_decrypt(blocks, 8);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x064ABA10, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xD5694B90, blocks["right"]);

  des.round_decrypt(blocks, 7);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xE967CD69, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x064ABA10, blocks["right"]);

  des.round_decrypt(blocks, 6);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x8A4FA637, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xE967CD69, blocks["right"]);

  des.round_decrypt(blocks, 5);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x77220045, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x8A4FA637, blocks["right"]);

  des.round_decrypt(blocks, 4);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xA25C0BF4, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x77220045, blocks["right"]);

  des.round_decrypt(blocks, 3);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xCC017709, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xA25C0BF4, blocks["right"]);

  des.round_decrypt(blocks, 2);
  BOOST_CHECK_BITWISE_EQUAL((int64_t)0xEF4A6544, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xCC017709, blocks["right"]);

  des.round_decrypt(blocks, 1);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xF0AAF0AA, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xEF4A6544, blocks["right"]);

  des.round_decrypt(blocks, 0);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xCC00CCFF, blocks["left"]);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xF0AAF0AA, blocks["right"]);
}

BOOST_AUTO_TEST_CASE(des_decrypt)
{
  uint64_t key = 0x133457799BBCDFF1;
  uint64_t raw_data = 0x123456789ABCDEF;
  uint64_t enc_data = 0x85E813540F0AB405;
  DES des(key); // initialize object

  BOOST_CHECK_BITWISE_EQUAL(raw_data, des.decrypt(enc_data));

  DES des_vector_key(0x0101010101010101);
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x95F8A5E5DD31D900, des_vector_key.decrypt(0x8000000000000000));
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0xDD7F121CA5015619, des_vector_key.decrypt(0x4000000000000000));
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x2E8653104F3834EA, des_vector_key.decrypt(0x2000000000000000));
  BOOST_CHECK_BITWISE_EQUAL((uint64_t)0x4BD388FF6CD81D4F, des_vector_key.decrypt(0x1000000000000000));
}

BOOST_AUTO_TEST_CASE(des_encryptN_decryptN)
{
  std::vector<uint64_t> raw_blocks, copy_blocks = {
    0x95F8A5E5DD31D900, 
    0xDD7F121CA5015619, 
    0x2E8653104F3834EA};
  uint64_t gamma = 0x4BD388FF6CD81D4F;
  uint64_t key = 0x133457799BBCDFF1;
  
  DES des(key);
  
  des.encryptN(raw_blocks, gamma);
  des.decryptN(raw_blocks, gamma);

  for (size_t i=0; i<raw_blocks.size(); i++)
    BOOST_CHECK_BITWISE_EQUAL(raw_blocks[i], copy_blocks[i]);
}