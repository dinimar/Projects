#include <iostream>
#include <cstring>

using namespace std;

struct chaff
{
	char dross[20];
	int slag;
};

const int SIZE = 2*(20 + 4); // 20 chars and 1 int (2 objects)
char s_buffer[SIZE];

int main(int argc, char const *argv[])
{
	char str1[] = "Rubbish";
	char str2[] = "Not rubbish";

	// on heap
	char *h_buffer = new char[SIZE];
	chaff *h_cha_arr = new(h_buffer) chaff[2];

	// initializing
	strcpy(h_cha_arr[0].dross, str1);
	h_cha_arr[0].slag = strlen(str1);
	strcpy(h_cha_arr[1].dross, str2);
	h_cha_arr[1].slag = strlen(str2);

	for(int i=0;i<2;i++)
	{
		cout << h_cha_arr[i].dross << " (" << h_cha_arr[i].slag << ")\n"; 
	}

	// on stack
	chaff *s_cha_arr = new(s_buffer) chaff[2];

	return 0;
}