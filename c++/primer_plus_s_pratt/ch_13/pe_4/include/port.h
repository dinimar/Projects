#ifndef PORT_H_
#define PORT_H_
#include <iostream>
using namespace std;
class Port
{
private:
    char *brand;
    char style[20]; // i.e., tawny, ruby, vintage
    int bottles;


    void CopyString(char * dest, const char * src);
    void InitCharArrays();
public:
    // All methods are only defined. 
    // No one is redefined because 
    // there is no inheritance. 

    Port(const char *br = "none", const char *st = "none", int b = 0);
    virtual ~Port() { delete[] brand; }
    
    Port(const Port &p);     // copy constructor
    // assignment operator
    // can't be virtual because it's not inherited
    Port & operator=(const Port &p);
    
    Port & operator+=(int b); // adds b to bottles
    Port & operator-=(int b); // subtracts b from bottles, if available 
    int BottleCount() const { return bottles; }
    
    virtual void Show() const;
    // can't be virtual because friend isn't member function
    // either cannot be inherited
    friend ostream & operator<<(ostream &os, const Port &p);
};
#endif