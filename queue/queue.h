#ifndef QUEUE_H
#define QUEUE_H
#include "status.h"

typedef void* QUEUE;

//initializes empty queue with null ptrs for front and back
//PRECONDITION: None
//POSTCONDITION: returns ptr to an empty queue object
QUEUE queue_init_default(void);

//pushes an item to the back of the queue
//PRECONDITION: hQueue is the handle of a valid queue object
//POSTCONDITION: returns SUCCESS if item successfully enqueued,
//	FAILURE otherwise.
Status queue_enqueue(QUEUE hQueue, int item);

//removes an item from the front of the queue
//PRECONDITION: hQueue is the handle of a valid queue object.
//POSTCONDITION: returns SUCCESS if removes the first item, returns
//	FAILURE if queue is empty
Status queue_service(QUEUE hQueue);

//returns whether or not the queue is empty
//PRECONDITION: none
//POSTCONDITION: Returns TRUE if queue is empty, FALSE if queue is invalid or non empty
Boolean queue_empty(QUEUE hQueue);

//returns the value of the item at the front of the queue
//PRECONDITION: hQueue is handle to valid queue object, pStatus is either a ptr to
//	a valid Status object or NULL.
//POSTCONDITION: returns int value of item at the front of the queue.
int queue_front(QUEUE hQueue, Status* pStatus);

//destroys & frees the queue
//PRECONDITION: none
//POSTCONDITION: all memory associated with phQueue is guaranteed to be freed, and the
//	dangling pointer has killed/set to NULL.
void queue_destroy(QUEUE* phQueue);

#endif