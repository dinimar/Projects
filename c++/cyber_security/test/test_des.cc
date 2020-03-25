#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include <map>
#include <string>
#include "des.h"

BOOST_AUTO_TEST_CASE ( des_nth_bit )
{
  int64_t a = 2;

  BOOST_CHECK_EQUAL(0, DES::get_nth_bit(0, a));
  BOOST_CHECK_EQUAL(1, DES::get_nth_bit(1, a));
}

BOOST_AUTO_TEST_CASE( des_permutation )
{
  int64_t data = 0x123456ABCD132536;    // raw data
  int64_t ip_data = 0x14A7D67818CA18AD; // data after initial permutation

  BOOST_CHECK_BITWISE_EQUAL(ip_data, DES::permutate(data, DES::ip_table));
}

BOOST_AUTO_TEST_CASE( des_rotl32 )
{
  int32_t rotation_key_mask = 0b00001111111111111111111111111111;

  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 0));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 1));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 14));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 28));
}

BOOST_AUTO_TEST_CASE( des_divide_key )
{
  int64_t key = 0x00FFFFFFFFFFFFFF;    // raw key
  
  std::map<std::string, int32_t> key_parts = DES::divide_perm_key(key); 

  BOOST_CHECK_BITWISE_EQUAL(key_parts["left"], key_parts["right"]);
}

BOOST_AUTO_TEST_CASE( des_restore_key )
{
  std::map<std::string, int32_t> key_parts;
  key_parts["left"] = 0x0FFFFFFF;
  key_parts["right"] = 0x0FFFFFFF;

  int64_t rest_key = DES::restore_key(key_parts);

  BOOST_CHECK_BITWISE_EQUAL(0x00FFFFFFFFFFFFFF, rest_key);
}
// BOOST_AUTO_TEST_CASE( des_encrypt )
// {
//   int64_t key = 0x0101010101010101;
//   int64_t data = 0x95F8A5E5DD31D900;
  
//   DES des(key);  // initialize object

//   BOOST_CHECK_BITWISE_EQUAL(0x8000000000000000, des.encrypt(data));
// }
