#include <stdio.h>

#define offsetof(TYPE, MEMBER) ((unsigned int)(&((TYPE *)0)->MEMBER))
#define struct_addr(MEMBER_ADDR, TYPE, MEMBER) \
		((TYPE *)(((unsigned int)MEMBER_ADDR) - (offsetof(TYPE, MEMBER))))

typedef struct {
	int a;
	int b;
} TEST;

int main(void)
{
	TEST test;

	//printf("%d\n", *(int *)0); //segment error
	//printf("%d\n", ((TEST *)0)->b); //segment error
	printf("%p\n", &((TEST *)0)->b); //ok
	printf("offsetof(TEST, b) = <%u>\n", offsetof(TEST, b));
	printf("addr(test) = <%p>\n", &test);
	printf("struct_addr(&test->b, TEST, b) = <%p>\n", \
		struct_addr(&test.b, TEST, b));

	return 0;
}
