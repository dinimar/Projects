//
// Created by Dinir Imameev on 12/25/19.
// Github: @dinimar
//

#ifndef STRING_LIB_STACK_H
#define STRING_LIB_STACK_H

// stack.h -- class declaration for the stack ADT
typedef unsigned long Item;
class Stack
{
private:
    enum {MAX = 10}; // constant specific to class
    Item * pitems; // holds stack items
    int size; // number of elements in stack
    int top; // index for top stack item
public:
    Stack(int n = MAX); // creates stack with n elements
    Stack(const Stack & st); // copy operator
    Stack & operator=(const Stack & st); // assignment operator
    ~Stack();
    bool isempty() const;
    bool isfull() const;
    // push() returns false if stack already is full, true otherwise
//    bool push(const Item & item); // add item to stack
//    // pop() returns false if stack already is empty, true otherwise
//    bool pop(Item & item); // pop top into item
};

#endif //STRING_LIB_STACK_H
