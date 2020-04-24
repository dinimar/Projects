#include "diffie-hellman.h"

namespace ENCRYPTION
{
namespace DIFFIE_HELLMAN
{
cpp_int modExp(const cpp_int &g, const cpp_int &x, const cpp_int p)
{
    using boost::multiprecision::pow;
    using boost::multiprecision::powm;

    return powm(g, x, p);
}

cpp_int xLower(const cpp_int & p)
{
    using namespace boost::multiprecision;
    using namespace boost::random;

    // Generate integers in a given range using uniform_int,
    // the underlying generator is invoked multiple times
    // to generate enough bits:
    //
    mt19937 mt;
    uniform_int_distribution<cpp_int> ui(0, cpp_int(1) << 1024);

    return ui(mt) % p;    
}

cpp_int publicSessionKey(const cpp_int &p, const cpp_int &g)
{
    cpp_int x = xLower(p);
    cpp_int X = modExp(g, x, p);

    cpp_int y = xLower(p);
    cpp_int Y = modExp(g, y, p);

    cpp_int sX = modExp(X, y, p);
    cpp_int sY = modExp(Y, x, p);

    assert(sX == sY); // in function test

    return sX;
}
} // namespace DIFFIE_HELMANN
} // namespace ENCRYPTION