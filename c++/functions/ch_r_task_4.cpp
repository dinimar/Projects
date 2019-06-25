#include <iostream>

using namespace std;

struct box
{
	char maker[40];
	float height;
	float width;
	float length;
	float volume;
};

void ShowBox(const box &boxx);

int main(int argc, char const *argv[])
{
	struct box boxx = { "TestBox", 1.5, 2.5, 3.5, 4.5 };
	ShowBox(boxx);

	return 0;
}

void ShowBox(const box &boxx)
{
	cout << "Maker: " << boxx.maker << endl;
	cout << "Height: " << boxx.height << endl;
	cout << "Width: " << boxx.width << endl;
	cout << "Length: " << boxx.length << endl;
	cout << "Volume: " << boxx.volume << endl;
}
