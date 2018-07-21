#include <stdio.h>
#include <string.h>

typedef struct {
	int data;
	Node* next;
} Node;

/*
	1. Travel link list
	2. Insert node
	3. Delete node
	4. Sort link list
*/

void travelList(Node* node) {
	/*
		1. while node not equal NULL
				print node.data
				node = node->next;
	*/
	while(node != NULL) {
		printf("%d-", node.data);
		node = node->next;
	}
}
/*
	append to end of list
*/
void append(Node** head, int data) {
	/*
		note: append to empty list
	*/
	/*
		1. 	Create new data node newNode
		2. 	If *head = NULL
				*head = newNode
				return
			lastNode = *head
			while lastNode->next != NULL
				lastNode = lastNode->next
			lastNode->next = newNode
			return
	*/
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if(*head = NULL) {
		*head = newNode;
		return;
	} 
	Node* lastNode = *head;
	while(lastNode->next != NULL){
		lastNode = lastNode->next;
	}
	lastNode->next = newNode;
	return;
}

void prepend(Node** head, int data) {
	/*
		note: prepend to empty list
	*/
	/*
		1. Create new data node newNode
		2.  If *head = NULL
				*head = newNode
				return
			newNode->next = *head
			*head = newNode		
	*/
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	if(*head == NULL) {
		*head = newNode;
		return;
	}
	newNode->next = *head;
	*head = newNode;
}

void insertAfter(Node* preNode, int data) {
	/*
		note: preNode must be not equal NULL
	*/
	if(preNode == NULL) {
		return;
	}
	
}