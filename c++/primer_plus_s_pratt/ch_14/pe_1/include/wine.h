#include <valarray>
#include "pair.h"

class Wine
{
private:
    typedef std::valarray<int> ArrayInt;
    typedef Pair<ArrayInt, ArrayInt> PairArray;
    std::string name;
    PairArray pair;
public:
    Wine(): name("Default wine"), pair({2000}, {1}){}
    // initialize label to l, number of years to y,
    // vintage years to yr[], bottles to bot[]
    Wine(const char * l, int y, const int yr[], const int bot[]);
    // initialize label to l, number of years to y,
    // create array objects of length y
    Wine(const char * l, int y);

    void GetBottles();      // initializes wine object
    std::string & Label();  // returns wine label
    void Show();
    int sum();              // returns number of all bottles
};