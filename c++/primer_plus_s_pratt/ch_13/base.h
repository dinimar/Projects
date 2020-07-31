#ifndef BASE_DER_H_
#define BASE_DER_H_


class Derived;
class Base
{
public:
    void foo1();
    virtual void foo2();

    operator Derived();
};

#endif