#include <iostream>

// Calculate the next fibonacci number
int calcFibNum(unsigned int n1, unsigned int n2){
	return n1 + n2;
}

// Generate Fibonacci sequence the nth number
int main(int argc, char const *argv[])
{
	unsigned int fibNum1 = 0;
	unsigned int fibNum2 = 1;
	
	int n = 0;
	std::cin >> n;

	if (n == 1) {
		std::cout << fibNum1;
	} else {
		std::cout << fibNum1 << ", " << fibNum2;
		for(int i=2;i<n;i++){
			unsigned int tmp = fibNum2;
			fibNum2 = calcFibNum(fibNum1, fibNum2);
			fibNum1 = tmp;
			if (i != n) std::cout << ", " << fibNum2; 
		}
	}

	std::cout << std::endl;

	return 0;
}
