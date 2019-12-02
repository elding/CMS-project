/* 
 *  Queues.h - Interface for Queue functionality
 *  by Sean Berkvens, 2019
 */

#include <Windows.h>
#include "frame.h"

const int iLength = 140;

typedef struct nodeText Node;
typedef struct item Item;
typedef Node* link;

struct textpayload {
	char message[iLength];
	
};

struct AudioPayload {
	char later[96000];
};


struct TextFrame {
	Header h;
	textpayload r;
};

struct AudioFrame {

	Header h;
	AudioPayload r;

};

struct nodeText {
	link pNext;
	TextFrame frame;
};


// Function Prototype
void InitQueue(void);
int IsQueueEmpty(void);
void AddToQueue(link);
link DeQueue(void);
