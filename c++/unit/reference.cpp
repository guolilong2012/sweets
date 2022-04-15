#include <iostream>

using namespace std;

void swap(int &x, int &y)
{
	int temp;

	temp = x;
	x = y;
	y = temp;
}

int main(void)
{
	int i = 3, j = 4;

	swap(i, j);
	cout << "i = " << i << ", j = " << j << endl;

	return 0;
}
