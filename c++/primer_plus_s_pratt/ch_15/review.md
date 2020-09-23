## 1. What’s wrong with the following attempts at establishing friends?
1. Friend member is declared before class declaration. In that case, we need move all clasp class declaration before snap class or perform forward declaration of clasp class.
    ```
    class snap {
    friend clasp;
    ...
    };
    class clasp { ... };
    ```


2. snip function requires muff class and cuff class doesn't know anything about muff class. Solution - forward declaration for muff class.
    ```
    class cuff {
    public:
    void snip(muff &) { ... }
    ...
    };
    class muff {
    friend void cuff::snip(muff &);
    ...
    };
    ```
3. muff class doesn't know about cuff::snip and therefore cuff class. Solution - set first muff class forward declaration; set second cuff class declaratio; set last muff class declaration.
    ```
    class muff {
    friend void cuff::snip(muff &);
    ...
    };
    class cuff {
    public:
    void snip(muff &) { ... }
    ...
    };
    ```
## 2. You’ve seen how to create mutual class friends. Can you create a more restricted form of friendship in which only some members of Class B are friends to Class A and some members of A are friends to B? Explain.
## 3. What problems might the following nested class declaration have?
```
class Ribs
{
private:
class Sauce
{
int soy;
int sugar;
public:
Sauce(int s1, int s2) : soy(s1), sugar(s2) { }
};
...
};
```
Derived classes don't have access to Sauce class.
## 4. How does throw differ from return?
``throw`` interrupts code execution and might stop program if there is no catch block.
## 5. Suppose you have a hierarchy of exception classes that are derived from a base exception class. In what order should you place catch blocks?
Firstly derived classes than to base classes.
## 6. Consider the Grand , Superb , and Magnificent classes defined in this chapter. Suppose pg is a type Grand * pointer that is assigned the address of an object of one of these three classes and that ps is a type Superb * pointer. What is the difference in how the following two code samples behave?
```
if (ps = dynamic_cast<Superb *>(pg))
    ps->say(); // sample #1

if (typeid(*pg) == typeid(Superb))
    ((Superb *) pg)->say(); // sample #2
```
In first case, whether pg is pointed to Superb object or not after if statement object that ps is pointed on is lost, because dynamic cast returns or pointer to passed object or 0.
In second case, there is no memory leak.
Also, in first case, if say() function in Grand class is non-virtual then ps->say() will call Grand::say() function. In second case, the programm will call Superb::say() whether Grand::say() virtual or not.
## 7. How is the static_cast operator different from the dynamic_cast operator?
static_cast allows either upcast or downcast conversion. static_cast produces error if it can't convert.
dynamic_cast allows only upcast conversion. dynamic_cast return 0 if it can't convert.