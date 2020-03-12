#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include "des.h"

BOOST_AUTO_TEST_CASE( des_encrypt )
{
  int64_t key = 0x0101010101010101;
  int64_t data = 0x95F8A5E5DD31D900;
  
  DES des(key);  // initialize object

  BOOST_CHECK_BITWISE_EQUAL(0x8000000000000000, des.encrypt(data));
}
