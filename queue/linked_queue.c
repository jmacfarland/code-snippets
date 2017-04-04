#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

/*******************************************************
	Author: Jamison MacFarland

	Purpose: Implements the queue data type using a
		linked list. Available functions include:
			 - Init default
			 - Enqueuing to the back of the queue
			 - Servicing from the front of the queue
			 - Checking if the queue is empty
			 - Getting the value of the item at the front
				of the queue
			 - Destroying the queue & freeing all memory
*******************************************************/

typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

//known type
struct queue
{
	Node* front;
	Node* back;
};

typedef struct queue Queue;

QUEUE queue_init_default(void)
{
	Queue* pQueue;

	pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue != NULL)
	{
		pQueue->front = NULL;
		pQueue->back = NULL;
	}
	return pQueue;
}

Status queue_enqueue(QUEUE hQueue, int item)
{
	Queue* pQueue = (Queue*)hQueue;
	Node* temp;

	temp = (Node*) malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}

	temp->data = item;
	temp->next = NULL;

	//if !empty, make prev back point to temp
	if (!queue_empty(pQueue))
		pQueue->back->next = temp;
	else //if empty, temp is front
		pQueue->front = temp;

	//add temp to back of queue
	pQueue->back = temp;

	return SUCCESS;
}

Status queue_service(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;
	Node* temp;

	if (queue_empty(hQueue))
	{
		return FAILURE;
	}
	
	temp = pQueue->front;
	pQueue->front = pQueue->front->next;
	free(temp);

	return SUCCESS;
}

Boolean queue_empty(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;

	if (pQueue != NULL)
	{
		if (pQueue->front == NULL)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int queue_front(QUEUE hQueue, Status* pStatus)
{
	Queue* pQueue = (Queue*)hQueue;

	if (queue_empty(hQueue)) //the queue is empty
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -8887888;
	}
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pQueue->front->data;
}

void queue_destroy(QUEUE* phQueue)
{
	Queue* pQueue = (Queue*)*phQueue;
	Node* temp;

	if (pQueue != NULL)
	{
		//free each node of the linked list
		while (pQueue->front != NULL)
		{
			temp = pQueue->front;
			pQueue->front = pQueue->front->next;
			free(temp);
		}

		free(pQueue);
		*phQueue = NULL;
	}
}