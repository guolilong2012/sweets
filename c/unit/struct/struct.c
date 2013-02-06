#include <stdlib.h>

struct node {
	int item;
};

struct node *make_node(int item)
{
	struct node *p = malloc(sizeof *p);

	p->item = item;

	return p;
}

int get_item(struct node *p)
{
	return p->item;
}
	
void free_node(struct node *p)
{
	free(p);
}
