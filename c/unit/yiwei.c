#include <stdio.h>

#define LITTLE_ENDIAN 0x11223344
#define BIG_ENDIAN 0x44332211
//#define BYTE_ORDER BIG_ENDIAN
#define BYTE_ORDER LITTLE_ENDIAN

typedef union test
{
	struct {
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned char a:3,
		      b:2,
		      c:1,
		      d:2;
#else
	unsigned char d:2,
		      c:1,
		      b:2,
		      a:3;
#endif
	};
	unsigned char e;
} TEST;

int main(void)
{
	int i = 0;
	int n = 0x12345678;
	TEST t;

	for (i=31; i>=0; i--)
	{
		printf("%d", (n>>i)&0x01);
		if (i%4 == 0)
			printf(" ");
	}
	printf("\n");

	t.e = 0x12;
	printf("t.a = %d\n", t.a);
	printf("t.b = %d\n", t.b);
	printf("t.c = %d\n", t.c);
	printf("t.d = %d\n", t.d);

	return 0;
}
