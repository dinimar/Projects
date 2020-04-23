#ifndef DIFFIE_HELLMAN_
#define DIFFIE_HELLMAN_
#include <cassert>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>

namespace ENCRYPTION
{
namespace DIFFIE_HELLMAN
{
using boost::multiprecision::cpp_int;
cpp_int modExp(const cpp_int &g, const cpp_int &x, const cpp_int p);
cpp_int publicSessionKey(const cpp_int &p, const cpp_int &g);
} // namespace DIFFIE_HELMANN
} // namespace ENCRYPTION

#endif