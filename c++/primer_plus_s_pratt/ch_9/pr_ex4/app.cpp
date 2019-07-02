#include "stack.h"
#include "customer.h"

int main(int argc, char const *argv[])
{
	customer cust = {"customer", 100};
	
	Stack st;

	st.push(cust);
	st.showTotal();

	st.pop(cust);
	st.showTotal();

	return 0;
}