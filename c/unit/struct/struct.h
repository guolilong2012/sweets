struct node;

extern struct node *make_node(int item);
extern int get_item(struct node *p);
extern void free_node(struct node *p);
