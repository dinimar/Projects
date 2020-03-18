#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include "des.h"

BOOST_AUTO_TEST_CASE( des_rotl32)
{
  int32_t rotation_key_mask = 0b00001111111111111111111111111111;


  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 0));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 1));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 14));
  BOOST_CHECK_BITWISE_EQUAL(rotation_key_mask, DES::rotl32(rotation_key_mask, 28, 28));
}

// BOOST_AUTO_TEST_CASE( des_encrypt )
// {
//   int64_t key = 0x0101010101010101;
//   int64_t data = 0x95F8A5E5DD31D900;
  
//   DES des(key);  // initialize object

//   BOOST_CHECK_BITWISE_EQUAL(0x8000000000000000, des.encrypt(data));
// }
