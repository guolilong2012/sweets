#include <iostream>

using namespace std;

int add(int a, int b)
{
	return a + b;
}

double add(double a, double b)
{
	return a + b;
}

int main(void)
{
	cout << add(1, 2) << endl << add(2.1, 3.4) << endl;

	return 0;
}
