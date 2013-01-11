#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct node {
	int item;
	struct node *next;
} node_t;

// Remove all nodes from the supplied list for which the
// supplied remove function returns true
// Returns the new head of the list.

typedef int (* remove_fn)(node_t const *v);

void remove_if(node_t **head, remove_fn rm)
{
	node_t *entry = NULL;
	node_t **cur = NULL;

	for (cur = head; *cur; ) {
		entry = *cur;
		if (rm(entry)) {
			*cur = entry->next;
			free(entry);
		} else
			cur = &entry->next;
	}
}

int my_remove_fn(node_t const *v)
{
	return v->item % 2 == 1;
}

void print(node_t *head)
{
	node_t *tmp = NULL;
	
	while (head)
	{
		tmp = head;
		head = head->next;
		printf("node <%d>\n", tmp->item);
		free(tmp);
	}
}

node_t *make_list(void)
{
	int i;
	node_t *head = NULL;
	node_t *tmp = NULL;

	for (i = N; i > 0; i--) {
		tmp = (node_t *)malloc(sizeof(node_t));
		tmp->item = i;
		tmp->next = head;
		head = tmp;
	}
		
	return head;
}

int main(void)
{
	node_t *head = make_list();
	remove_if(&head, my_remove_fn);
	print(head);

	return 0;
}	



