#define BOOST_TEST_MODULE test des
#include <boost/test/included/unit_test.hpp>
#include "des.h"

BOOST_AUTO_TEST_CASE( free_test_function )
/* Compare with void free_test_function() */
{
  DES des("123");
  BOOST_TEST(true);
}
