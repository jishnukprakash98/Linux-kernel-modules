
#include <stdlib.h>
#include <stdio.h>
#include "llist.h"


node *list_create(int new_data)
{
    node new_node;

   	node *new_list = (node *)malloc(sizeof (node));
    *new_list = (node)malloc(sizeof (node));
    
    new_node = *new_list;
    new_node->data = (int)new_data;
    new_node->next = NULL;
    return new_list;
}

void list_push(node *list,int value)
{
	//node temp = create_node();
	//temp->data = value;
	node head = *list;
	if(list == NULL){
		fprintf(stderr, "llist_add_inorder: list is null\n");
	}

	if(head->data == 0) {
		head->data = value;
	}
	else {
		node new_node = malloc(sizeof(node));
		new_node->data = value;
		new_node->next = head;
		*list = new_node;
		/*
		while(curr->next != NULL) {
			curr = curr->next;
		}
		curr->next = temp;
		*/
	}
}

void list_print(node *list) {
	node curr = *list;
	printf("\nLIST : " );
	while(curr != NULL) {
		printf("%d ",curr->data );
		curr = curr->next;
	}
}
