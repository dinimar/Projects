#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include "person.h"
#include <random>

class PokerPlayer: virtual public Person
{
private:
    std::random_device r;
    std::default_random_engine mEngine{r()};
    std::uniform_int_distribution<int> mUniformDist{1, 52};
public:
    PokerPlayer(string firstName="Poker", string lastName="Player")
    : Person(firstName, lastName){};

    void Set();
    int Draw();
    void Show();

    ~PokerPlayer() = default;
};

#endif