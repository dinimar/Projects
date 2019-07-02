#ifndef STACK_H_
#define STACK_H_ 
#include "customer.h"

typedef customer Item;

class Stack
{
private:
	enum {MAX = 10};
	// constant specific to class
	Item items[MAX];
	// holds stack items
	int top;
	// index for top stack item

	// total amount of money
	double total;
public:
	Stack();
	bool isempty() const;
	bool isfull() const;
	// push() returns false if stack already is full, true otherwise
	bool push(const Item & item);
	// add item to stack
	// pop() returns false if stack already is empty, true otherwise
	bool pop(Item & item);// pop top into item
	void showTotal() const;
};
#endif