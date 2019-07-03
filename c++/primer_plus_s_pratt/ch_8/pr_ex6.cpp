#include <iostream>
#include <cstring>

using namespace std;

template<typename T> T maxn(T [], int);
template<> const char * maxn(const char *[], int);

int main(int argc, char const *argv[])
{
	int arr_int[] = {0, 1, 2, 3, 4, 5};
	double arr_dou[] = {3.1, 2.4, 1.5, 0.6};

	char str1[] = "abcd";
	char str2[] = "abc";
	char *arr_cha[] = {str1, str2};
	
	cout << maxn(arr_int, 6) << endl;
	cout << maxn(arr_dou, 4) << endl;
	cout << maxn(arr_cha, 2) << endl;

	return 0;
}

template<typename T> T maxn(T arr[], int len)
{
	T max = arr[0];
	for(int i=1;i<len;i++){
		max = max < arr[i] ? arr[i] : max;
	}

	return max;
}

template<> const char * maxn(const char *arr[], int len)
{
	const char *max = arr[0];
	for(int i=1;i<len;i++){
		max = strlen(max) < strlen(arr[i]) ? arr[i] : max;
	}

	return max;	
}