
#include<Windows.h>


struct Header {
	short int sid;        //Sender ID
	short int rid;		  // Reciever ID
	int priority;		  // Priority of message
	int isAudio;		  // Flag for audio messages vs text
};
