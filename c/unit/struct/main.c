#include <stdio.h>

#include "struct.h"

int main(void)
{
	struct node *p = make_node(3);

	printf("get_item:<%d>\n", get_item(p));
//	printf("p->item:<%d>\n", p->item); //error
	printf("p->item:<%d>\n", get_item(p));

	free_node(p);

	return 0;
}
