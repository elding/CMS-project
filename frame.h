
#include<Windows.h>


struct Header {
	short int sid;        //Sender ID
	short int rid;		  // Reciever ID
	char priority;		  // Priority of message
	int isAudio;
};
