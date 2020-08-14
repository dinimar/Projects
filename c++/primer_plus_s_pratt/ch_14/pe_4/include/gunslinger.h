#ifndef GUNSLINGER_H_
#define GUNSLINGER_H_
#include "person.h"

class Gunslinger: virtual public Person
{
private:
    double mDrawTime;
public:
    Gunslinger(string firstName="Typical", string lastName="Gunslinger", double drawTime=0.0)
    :Person(firstName, lastName), mDrawTime(drawTime){};

    void Set();
    double Draw();
    void Show();

    ~Gunslinger() = default;
};

#endif