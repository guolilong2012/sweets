#include <stdio.h>

int main(void)
{
	double d = 0.78;
	int n1 = (int)d;
	int n2 = *(int *)&d;

	printf("d = <%lf>\n", d);
	printf("(int)d = <%d>\n", n1);
	printf("*(int *)&d = <%d>\n", n2);

	return 0;
}

#if 0
d = <0.780000>
(int)d = <0>
*(int *)&d = <-1889785610>
#endif
