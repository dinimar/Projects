#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include "des.h"

BOOST_AUTO_TEST_CASE( des_encrypt )
{
  std::vector<int8_t> key = {1, 2, 3, 4, 5, 6, 7};
  DES des(key);
  BOOST_TEST(true);
}
