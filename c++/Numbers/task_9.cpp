#include <iostream>

int numConvert(int in_num, int base, int exp);

int main(int argc, char const *argv[])
{
	int bin = 0;
	int dec = 0;

	std::cout << "Enter a binary number\n";
	std::cin >> bin;
	std::cout << "Enter a decimal number\n";
	std::cin >> dec;

	std::cout << "Result:" << std::endl;
	std::cout << bin << "->" << numConvert(bin, 2, 10) << std::endl;
	std::cout << dec << "->" << numConvert(dec, 10, 2) << std::endl;
	
	return 0;
}

int numConvert(int in_num, int base, int exp)
{
	int res = 0;
	int mult = 1;

	while (in_num > 0){
		res += (in_num % exp) ? mult : 0;
		in_num /= exp;
		mult *= base; 
	}

	return res;
}