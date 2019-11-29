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
	char later[2000];
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
