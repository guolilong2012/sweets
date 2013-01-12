#include <stdio.h>
#include <string.h>

#define SWAP(a, b) \
	do { \
		(a) = (a) + (b); \
		(b) = (a) - (b); \
		(a) = (a) - (b); \
	} while(0)

char *itostring(int num, int base, char buf[])
{
	int i = 0;
	int len = 0;
	char hex[] = "0123456789abcdef";

	do {
		buf[i++] = hex[num%base];
		num /= base;
	} while (num);
	buf[i] = '\0';

	len = strlen(buf);
	for (i = 0; i < len/2; i++) 
		SWAP(buf[i], buf[len-1-i]);

	return buf;
}

int hex_index(char c)
{
	int i;
	char hex[] = "0123456789abcdef";
	int len = strlen(hex);

	for (i = 0; i < len; i++) {
		if (hex[i] == c)
			return i;
	}

	return 0;
}

int stringtoi(char buf[], int base)
{
	int i;
	int num = 0;
	int len = strlen(buf);
	int mybase = 1;

	for (i = len-1; i >= 0; i--) {
		num += hex_index(buf[i]) * mybase;
		mybase *= base;
	}

	return num;
}

int main(void)
{
	char buf[10];
	int num = 100;
	int base = 16;

	printf("itostring(%d, %d, buf) = <%s>\n", num, base, itostring(num, base, buf));
	printf("stringtoi(%s, %d) = <%d>\n", buf, base, stringtoi(buf, base));

	return 0;
}
