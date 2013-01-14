#include <stdio.h>

#define SWITCH(S) char *_S = S; if (0)
#define CASE(S) } else if (strcmp(_S, S) == 0) {switch (1) { case 1
#define BREAK }
#define DEFAULT } else {switch (1) { case 1

int main(void)
{
	char buf[256];

	printf("\nString - Enter your string: ");
	scanf("%s", buf);

	SWITCH (buf) {
		CASE ("abcdef"):
			printf("B1!\n");
			BREAK;
		CASE ("ghijkl"):
			printf("C1!\n");
			BREAK;
		DEFAULT:
			printf("D1!\n");
			BREAK;
	}
}

#if 0
int main(void)
{
 char buf[256];

 printf("\nString - Enter your string: ");
 scanf("%s", buf);

 char *_S = buf; if (0) {
  } else if (strcmp(_S, "abcdef") == 0) {switch (1) { case 1:
   printf("B1!\n");
   };
  } else if (strcmp(_S, "ghijkl") == 0) {switch (1) { case 1:
   printf("C1!\n");
   };
  } else {switch (1) { case 1:
   printf("D1!\n");
   };
 }
}
#endif
