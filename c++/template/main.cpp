#include <iostream>
using namespace std;

#include "template.h"

int main(void)
{
	Buffer <int, 10> intbuf10;

	for (int i = 0; i < 10; i++)
		intbuf10.v[i] = i;
	for (int i = 0; i < 10; i++)
		cout << intbuf10.v[i] << endl;

	int a = 2;
	cout << "power(2, 3) = " << power(a, 3) << endl;	

	return 0;
}
