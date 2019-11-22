/* 
 *  Queues.h - Interface for Queue functionality
 *  by Sean Berkvens, 2019
 */


#include "frame.h"

const int iLength = 140;

typedef struct node Node;
typedef struct item Item;
typedef Node* link;

struct item {
	char message[iLength];
	short int sid;        //Sender ID
	short int rid;		  // Reciever ID
	char priority;		  // Priority of message
	short int seqNum;	  // Sequence number of a message
	char later[25];
};


struct Frame {
	Header h;
	item r;
};

struct node {
	link pNext;
	Frame frame;
};


// Function Prototype
void InitQueue(void);
int IsQueueEmpty(void);
void AddToQueue(link);
link DeQueue(void);
