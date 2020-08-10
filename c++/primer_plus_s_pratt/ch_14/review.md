## 1. For each of the following sets of classes, indicate whether public or private derivation is more appropriate for Column B:
```
class PolarBear: private Bear
class Home: public Kitchen
class Programmer: public Person
class HorseAndJockey: public Person
class Driver: public Person, private Automobile
```
## 2. Given that the Gloam version of tell() should display the values of glip and fb , provide definitions for the three Gloam methods.

```
Gloam::Gloam(int g = 0, const char * s = "C++"): fb(s)
{
    glip = g;
}

Gloam::Gloam(int g = 0, const Frabujous & f): fb(f)
{
    glip = g;
}

void Gloam::tell()
{
    std::cout   << glip << std::endl
                << fb   << std::endl;
}
```

## 3. Given that the Gloam version of tell() should display the values of glip and fab ,provide definitions for the three Gloam methods.
```
Gloam::Gloam(int g = 0, const char * s = "C++"):
Frabujous(s)
{
    glip = g;
}

Gloam::Gloam(int g = 0, const Frabujous & f): Frabujous(f)
{
    glip = g;
}

void Gloam::tell()
{
    std::cout << glip << std::endl;
    Frabujous::tell();
}
```

## 4. Suppose you have the following definition, based on the Stack template of Listing 14.13 and the Worker class of Listing 14.10: ```Stack<Worker *> sw;```Write out the class declaration that will be generated. Just do the class declaration, not the non-inline class methods.
```
template <Worker *>
class Stack
{
private:
    enum {MAX = 10};    // constant specific to class
    Type items[MAX];    // holds stack items
    int top;            // index for top stack item
public:
    Stack();
    bool isempty();
    bool isfull();
    bool push(const Worker * item); // add item to stack
    bool pop(Worker * item);        // pop top into item
};
```
## 5.1 Use the template definitions in this chapter to define the following:
- An array of string objects
```
std::valarray<std::string>
```
- A stack of arrays of double
```
Stack<std::valarray<double>>
```
- An array of stacks of pointers to Worker objects
```
std::valarray<Stack<Worker*>>
```
## 5.2 How many template class definitions are produced in Listing 14.18?
4 template class definitions are produced.
## 6. Describe the differences between virtual and nonvirtual base classes.
Virtual base class provide facility to eliminate duplicates of base class in derived class. For instance, in case of diamond problem. A derived class indirectly derived base class must explicitly call base class constructor in its consturctor.
Name ambiguity resolved via dominance rule i.e. the last derived class of multiple derived classes that redefines base-class method provides the nex derived classes its definition.

Non-virtual base class doesn't provide facility like virtual one. A derived class will have two copies of base class in case of diamond problem. Call of indirect base class consturctor is illegal for non-virtual base classes.