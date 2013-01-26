#include <stdio.h>

#define N -1

int count_bit_1(int n)
{
	int cnt = 0;

	while (n) {
		cnt++;
		n &= n - 1;
	}

	return cnt;
}

int main(void)
{
	printf("%d has <%d> \'1\'\n", N, count_bit_1(N));

	return 0;
}
