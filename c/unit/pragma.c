#include <stdio.h>
#include <netinet/in.h>

//字节对齐
//arm - 4(int) 2(short)
//mips、x86、powerpc - 可一字节

//字节序
//arm、x86、mips小端
//powerpc大端

#pragma pack(1)

typedef struct test {
	char a;
	short b;
	int c;
} TEST;

#pragma pack()

int main(void)
{
	int i = 0;
	char *n = NULL;
	TEST *t1 = NULL;

	int size = 0x11223344;

	size = ntohl(size);
	printf("size = 0x%x\n", size);

#if 0
	unsigned char arr[] = {1, 3, 2, 7, 6, 5, 4};
	for (i=0; i<sizeof(arr); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	n = &arr[0];
	printf("0x%x\n", *(int *)n);
	n = &arr[1];
	printf("0x%x\n", *(int *)n);
	n = &arr[2];
	printf("0x%x\n", *(int *)n);
	n = &arr[3];
	printf("0x%x\n", *(int *)n);

	t1 = &arr[0];
	printf("t1->a = 0x%x\n", t1->a);
	printf("t1->b = 0x%x\n", t1->b);
	printf("t1->c = 0x%x\n", t1->c);
#endif

#if 1
	unsigned char arr[] = {1, 3, 2, 7, 6, 5, 4, 8};
	for (i=0; i<sizeof(arr); i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	n = &arr[0];
	printf("0x%x\n", *(int *)n);
	n = &arr[1];
	printf("0x%x\n", *(int *)n);
	n = &arr[2];
	printf("0x%x\n", *(int *)n);
	n = &arr[3];
	printf("0x%x\n", *(int *)n);

	t1 = &arr[0];
	printf("t1->a = 0x%x\n", t1->a);
	printf("t1->b = 0x%x\n", t1->b);
	printf("t1->c = 0x%x\n", t1->c);
#endif

#if 0
	TEST t = {0x01, 0x0203, 0x04050607};
	unsigned char *p = &t;
	printf("sizeof(TEST) = %d\n", sizeof(TEST));
	for (i=0; i<sizeof(TEST); i++) {
		printf("%d ", p[i]);
	}
	printf("\n");
#endif

	return 0;
}

