## 1. What does a derived class inherit from a base class?
All public member functions except **special member functions** that includes constructor, copy constructor/assignment operator, destructor. Therefore, a derived class doesn't inherit **non-member functions** as friend functions.

## 2. What doesn’t a derived class inherit from a base class?
- constructor
- assignment operator
- copy constructor
- destructor

## 3. Suppose the return type for the baseDMA::operator=() function were defined as void instead of baseDMA & .What effect, if any, would that have? What if the return type were baseDMA instead of baseDMA & ?


**void** return type makes impossible to perform multiple (nested) assignment operation. For example:
***
void baseDMA::operator=(const baseDMA & dma)
{
    //
}

baseDMA t(1);

t = t = t;  // only first assignment works

// second assignment:
// t.operator(void);
// second one makes a compilation error because of void passed to assignment operator
***

**baseDMA** return type leads to copy constuctor calls in case of multiple assignment. Example:
***
baseDMA baseDMA::operator=(const baseDMA & dma)
{
    //
}

baseDMA t(1);

t = t = t;

***
Because operator= attribute type


## 4. In what order are class constructors and class destructors called when a derived-class object is created and deleted?

Created:
- Base class constructor
- Derived class consturctor

Deleted:
- Derived class destructor
- Base class constructor

## 5. If a derived class doesn’t add any data members to the base class, does the derived class require constructors?
It depends on whether we initialize base class data members (if they exist):
- if yes, we need constructor with member initializer list for base-class initialization
- if no, we don't need constructor

Also, compiler, by default, creates default constructor.

## 6. Suppose a base class and a derived class both define a method with the same name and a derived-class object invokes the method. What method is called?
It depends on variable type and function type (virtual or not):

|             | Base       | Base *        | Derived       | Derived *     |
|-------------|------------|---------------|---------------|---------------|
| virtual     | Base.foo() | Derived.foo() | Derived.foo() | Derived.foo() |
| non-virtual | Base.foo() | Base.foo()    | Derived.foo() | Derived.foo() |

## 7. When should a derived class define an assignment operator?

If a derived class have extra members. You need to define assignment operator with base-class part assignment and assignment for extra members.

In other case, default assignment operator automatically copies base-class part.

## 8. Can you assign the address of an object of a derived class to a pointer to the base class? Can you assign the address of an object of a base class to a pointer to the derived class?

1. Yes, it can be implemented without explicit type cast
2. No, it requires explicit type cast (down cast)

## 9. Can you assign an object of a derived class to an object of the base class? Can you assign an object of a base class to an object of the derived class?
1. Yes, but in that case we have access to the base-class part. The reason why is slicing mechanism.
2. If the base class have conversion or the derived class have constructor with base-class argument.

## 10. Suppose you define a function that takes a reference to a base-class object as an argument. Why can this function also use a derived-class object as an argument?
Because function makes implicit upcast conversion to the base class.

## 11. Suppose you define a function that takes a base-class object as an argument (that is, the function passes a base-class object by value).Why can this function also use a derived-class object as an argument?
Because function makes implicit upcast conversion to the base class. But in that case we have access only to base-class members. The reason why is slicing mechanism.

## 12. Why is it usually better to pass objects by reference than by value?
We avoid copy constructor call when we pass objects by reference.

## 13. Suppose Corporation is a base class and PublicCorporation is a derived class.Also suppose that each class defines a head() member function, that ph is a pointer to the Corporation type, and that ph is assigned the address of a PublicCorporation object. How is ph->head() interpreted if the base class defines head() as a
### a. Regular nonvirtual method
### b. Virtual method

#### a. Corporation::head()
#### b. PublicCorporation::head()

## 14. What’s wrong, if anything, with the following code?
1. If you overload function in derived class you also need to redefine old function. Otherwise you loose function inherited from base class.
2. In that code *is-a* relationship is not suitable. The House class *is-not-a* the Kitchen class. The *has-a* is more suitable. The Kitchen class should be member of the House class. And both of the classes should be inherited from some abstract class that can storage area and its parameters.