#include <iostream>
#include <ctime>
#include <cmath>
#include <boost/dynamic_bitset.hpp>
#include <vector>
#include <cassert>

using std::string;
using boost::dynamic_bitset;

uint64_t modexp(uint64_t base, uint64_t exp, uint64_t modNum)
{
    while (exp != 0)
    {
        base = base * exp;
        exp--;
    }

    return base % modNum;
}

std::string hexStr2binStr(const string & hexStr)
{
    std::string bitStr = "";

    for (const auto & ch: hexStr)
    {
        switch (ch)
        {
        case '0':
            bitStr.append("0000");
            break;
        case '1':
            bitStr.append("0001");
            break;
        case '2':
            bitStr.append("0010");
            break;
        case '3':
            bitStr.append("0011");
            break;
        case '4':
            bitStr.append("0100");
            break;
        case '5':
            bitStr.append("0101");
            break;
        case '6':
            bitStr.append("0110");
            break;
        case '7':
            bitStr.append("0111");
            break;
        case '8':
            bitStr.append("1000");
            break;
        case '9':
            bitStr.append("1001");
            break;
        case 'a':
            bitStr.append("1010");
            break;
        case 'b':
            bitStr.append("1011");
            break;
        case 'c':
            bitStr.append("1100");
            break;
        case 'd':
            bitStr.append("1101");
            break;
        case 'e':
            bitStr.append("1110");
            break;
        case 'f':
            bitStr.append("1111");
            break;
        }
    }

    return bitStr;
}

dynamic_bitset<> hexStr2bitSet(const string & hexStr)
{   
    string str = hexStr2binStr(hexStr);

    return dynamic_bitset<>(str);
}

uint64_t publicSessionKey(const uint64_t & p, const uint64_t & g)
{
    uint64_t x = std::rand() % 37;
    uint64_t X = modexp(g, x, p);

    uint64_t y = std::rand() % 37;
    uint64_t Y = modexp(g, y, p);

    uint64_t sX = modexp(X, y, p);
    uint64_t sY = modexp(Y, x, p);

    assert(sX == sY);

    return sX;
}

int main(int argc, char** argv)
{
    std::srand(std::time(nullptr));     // use current time as seed for random generator

    // uint64_t p = 37;     // set p to 37
    // uint64_t g = 5;      // set g to 5

    std::string hexString = "ffffffffffffffffc90fdaa22168c234c4c6628b80dc1cd129024e088a67cc74020bbea63b139b22514a08798e3404ddef9519b3cd3a431b302b0a6df25f14374fe1356d6d51c245e485b576625e7ec6f44c42e9a637ed6b0bff5cb6f406b7edee386bfb5a899fa5ae9f24117c4b1fe649286651ece45b3dc2007cb8a163bf0598da48361c55d39a69163fa8fd24cf5f83655d23dca3ad961c62f356208552bb9ed529077096966d670c354e4abc9804f1746c08ca237327ffffffffffffffff"; 
   
    std::cout << hexStr2bitSet(hexString);
    // constexpr size_t strSize = bitString.size(); 
    // bitset<384> p(bitString);


    // std::cout << p;
    // uint64_t a = std::rand() % 37;        // generate a, random int % 37         
    // uint64_t A = modexp(g, a, p);    // generate A = (g**a) % p

    // uint64_t b = std::rand() % 37;        // generate b, random int % 37         
    // uint64_t B = modexp(g, b, p);    // generate B = (g**b) % p


    // uint64_t sA = modexp(B, a, p);   // generate session key, s = (B**a) % p
    // uint64_t sB = modexp(A, b, p);   // generate session key, s = (A**b) % p

    // assert(sA == sB);

    // publicSessionKey()

    return 0;
}