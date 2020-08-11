#include "wine.h"

Wine::Wine(const char * l, int y, const int yr[], const int bot[])
{
    name = l;
    pair = PairArray(std::valarray<int>(yr, y), std::valarray<int>(bot, y));
}

Wine::Wine(const char * l, int y)
{
    name = l;
    pair = PairArray(std::valarray<int>(y), std::valarray<int>(y));
}

void Wine::GetBottles()
{
    using std::cout;
    using std::cin;

    cout << "Enter " << name << "data for " << pair.first().size() << " year(s):\n";

    for(size_t i=0; i<pair.first().size(); ++i)
    {
        cout << "Enter year: ";
        cin >> pair.first()[i];     // init year
        cout << "Enter bottles for that year: ";
        cin >> pair.second()[i];    // init number of bottles
    }
}

std::string & Wine::Label()
{
    return name;
}

void Wine::Show()
{
    using std::cout;
    cout << "Wine: " << name << '\n'
         << "\t\tYear\t\tBottles\n";
    for(size_t i=0; i<pair.first().size(); ++i)
    {
        cout << "\t\t" << pair.first()[i] << "\t\t" << pair.second()[i] << '\n';
    }  
}

int Wine::sum()
{
    return pair.second().sum();
}
