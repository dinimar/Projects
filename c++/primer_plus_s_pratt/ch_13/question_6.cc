#include <iostream>
#include "base.h"
#include "derived.h"

Base::operator Derived(){return Derived();}
void Base::foo1() { std::cout << "Base foo1()" << std::endl; }
void Base::foo2() { std::cout << "Base foo2()" << std::endl; }

void Derived::foo1() { std::cout << "Derived foo1()" << std::endl; }
void Derived::foo2() { std::cout << "Derived foo2()" << std::endl; }


int main()
{
    Base b = Derived();
    Base * bPtr = new Derived();
    Derived d = Derived();
    Derived dB = Base();

    b.foo1();
    b.foo2();

    bPtr->foo1();
    bPtr->foo2();

    d.foo1();
    d.foo2();
}