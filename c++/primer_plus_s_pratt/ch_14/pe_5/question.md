## Why is no assignment operator defined?
Because there is no class with pointer type attribute. Default assignment operator in that case works fine.
## Why are ShowAll() and SetAll() virtual?
Because they are redefined in derived classes. For each class we need own virtual table for its functions. In case of 'with-no-virtual' base class all derived class used base class functions.
## Why is abstr_emp a virtual base class?
Because we use virtual inheritance to solve 'diamond problem'. Virtual inheritance prevents multiple copies in derived class.
## Why does the highfink class have no data section?
Because it derives data members from fink and manager classes.
## Why is only one version of operator<<() needed?
Because it requires base class as type for argument. All derived classes upcasted to base class which is legal conversion.
## What would happen if the end of the program were replaced with this code?
```
abstr_emp tri[4] = {em, fi, hf, hf2};
for (int i = 0; i < 4; i++)
    tri[i].ShowAll();
```
Nothing because ShowAll() is virtual and it guarantees that derived-class function will be called.