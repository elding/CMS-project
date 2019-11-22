/* 
 *  Queues.cpp - Implementation of Queue functions
 *  by Sean Berkvens, 2019
 */

#include "Queues.h"
#include <stdlib.h>

static link pHead, pTail;		//Private pointers to head and tail of queue

void InitQueue(void){			//intialize the queue
	pHead = pTail = NULL;
}

int IsQueueEmpty(void){			//check if queue is empty - empty iff pHead is NULL
	return(pHead == NULL);
}
void AddToQueue(link pn) {		// Enqueue new node provided and instantiated in main
	if (IsQueueEmpty()) {
		pHead = pTail = pn;		//pHead only stored once for first node added
	}
	else {
		pTail->pNext = pn;		// old tail poins to new Node added
		pTail = pn;				// make pn the new tail
	}
	
	pTail->pNext = NULL;		// set pointer from last node to NULL - indicates end of queue
}
link DeQueue(void){
	link pTemp;					// holds current head
	if (IsQueueEmpty()) {
		return NULL;
	}
	else {
		pTemp = pHead;			//store current head
		pHead = pHead->pNext;	//next node becomes new head
		return (pTemp);			//return original head
	}
}