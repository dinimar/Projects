#include <iostream>
#include <ctime>
#include <cmath>
#include <cassert>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/random.hpp>

using boost::multiprecision::cpp_int;

cpp_int modExp(const cpp_int & g, const cpp_int & x, const cpp_int p)
{
    using boost::multiprecision::pow;
    using boost::multiprecision::powm;

    return powm(g, x, p);
}

cpp_int publicSessionKey(const cpp_int & p, const cpp_int & g)
{
    using namespace boost::multiprecision;
    using namespace boost::random;

    // Generate integers in a given range using uniform_int,
    // the underlying generator is invoked multiple times
    // to generate enough bits:
    //
    mt19937 mt;
    uniform_int_distribution<cpp_int> ui(0, cpp_int(1) << 1024);

    cpp_int x = ui(mt) % p;
    cpp_int X = modExp(g, x, p);

    cpp_int y = ui(mt) % p;
    cpp_int Y = modExp(g, y, p);

    cpp_int sX = modExp(X, y, p);
    cpp_int sY = modExp(Y, x, p);

    assert(sX == sY);   // in function test

    return sX;
}

int main(int argc, char** argv)
{
    cpp_int p = 0xffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b22514a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f83655d23dca3ad961c62f356208552bb9ed529077096966d670c354e4abc9804f1746c08ca237327ffffffffffffffff; 
    cpp_int g = 2;

    publicSessionKey(p, g);

    return 0;
}