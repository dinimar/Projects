#include <iostream>

int main(int argc, char const *argv[])
{
	float sum = 0;
	float rate = 0;
	float term_num = 0;

	std::cout << "Enter the sum of loan:" << std::endl;
	std::cin >> sum;
	std::cout << "Enter the rate:" << std::endl;
	std::cin >> rate;
	std::cout << "Enter the amount of terms:" << std::endl;
	std::cin >> term_num;

	std::cout << "Monthly payment" << std::endl;
	std::cout << (sum * (1.0+(rate/100))) / term_num << std::endl;
	
	return 0;
}