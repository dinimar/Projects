#include <iostream>

using namespace std;

template<typename T> T max5(T []);

int main(int argc, char const *argv[])
{
	int arr_int[] = {0, 1, 2, 3, 4};
	double arr_dou[] = {0.5, 1.5, 2.5, 3.5, 4.5};

	cout << max5(arr_int) << endl;
	cout << max5(arr_dou) << endl;

	return 0;
}

template<typename T> T max5(T arr[])
{
	T max = arr[0];
	for(int i=1;i<5;i++){
		max = max < arr[i] ? arr[i] : max;
	}

	return max;
}
