#ifndef BAD_DUDE_H_
#define BAD_DUDE_H_

#include "gunslinger.h"
#include "pokerplayer.h"

class BadDude: public Gunslinger, public PokerPlayer
{
private:
    /* data */
public:
    BadDude() {};

    void Set();
    double GDraw();
    int CDraw();
    void Show();

    ~BadDude() = default;
};


#endif