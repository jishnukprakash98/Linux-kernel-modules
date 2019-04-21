
struct LinkedList{
    int data;
    struct LinkedList *next;
 };

typedef struct LinkedList *node;        //Define node as pointer of data type struct LinkedList

/* llist_create: Create a linked list */
node *list_create(int new_data);

/* llist_push: Add to head of list */
void list_push(node *list, int value);

/* llist_print: print linked list */
void list_print(node *list);
