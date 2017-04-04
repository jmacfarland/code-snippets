/*********************************************************
	Program: Daily6
	Author: Jamison MacFarland
	Date: 2/8/2017
	Time spent: about an hour
	Purpose: This program reverses a linked list.
**********************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

Node* linkedList_reverse(Node* head);

int main(int argc, char* argv[])
{
	Node* head = NULL;
	int i;
	Node* temp;

	//set up a test list with values 9->8->7->...->0
	for (i = 0; i < 10; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory?\n");
			exit(1);
		}
		temp->data = i;
		temp->next = head;
		head = temp;
	}

	head = linkedList_reverse(head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

Node* linkedList_reverse(Node* head)
{
	Node* current = head;
	Node* next = NULL;
	Node* previous = NULL;

	while(current != NULL)//the last statement of this loop assigns the value of next to current, 
			//so if current == NULL, next == NULL and we are done
	{
		next = current->next;//shifts next forward to remember where the next node points
		current->next = previous;//makes the current node point to the previous node
		previous = current;//shifts previous forward
		current = next;//shifts next forward
	}
	
	return previous;//when the loop is done, current == NULL, so use previous node instead
}