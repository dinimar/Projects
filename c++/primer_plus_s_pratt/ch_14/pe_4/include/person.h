#ifndef PERSON_H_
#define PERSON_H_
#include <string>
using std::string;

class Person
{
private:
    string mFirstName;
    string mLastName;

protected:
    virtual void Get();

public:
    Person(string firstName="Person", string lastName="Person"): 
    mFirstName(firstName), mLastName(lastName){};

    virtual void Show();

    virtual void Set() = 0;

    virtual ~Person() = default;
};


#endif