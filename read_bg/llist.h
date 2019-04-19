/* llist.h
 * Generic Linked List
 */

struct LinkedList{
    int data;
    struct LinkedList *next;
 };

typedef struct LinkedList *node; //Define node as pointer of data type struct LinkedList
//static node head = NULL;
/* llist_create: Create a linked list */
node *list_create(int new_data);

/* llist_free: Free a linked list */
//void llist_free(llist *list);

/* llist_add_inorder: Add to sorted linked list */
//int llist_add_inorder(void *data, llist *list, 
                       

/* llist_push: Add to head of list */
void llist_push(node *list, int value);

/* llist_pop: remove and return head of linked list */
//void *llist_pop(llist *list);

/* llist_print: print linked list */
void list_print(node *list);