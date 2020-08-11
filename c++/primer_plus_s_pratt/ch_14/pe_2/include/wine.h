#include <valarray>
#include "pair.h"

typedef std::valarray<int> ArrayInt;
typedef Pair<ArrayInt, ArrayInt> PairArray;
using std::string;

class Wine: private PairArray, private string
{
private:
    // std::string name;
    // PairArray pair;
public:
    Wine(): string("Default wine"), PairArray({2000}, {1}){}
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