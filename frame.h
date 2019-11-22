
#include<Windows.h>


struct Header {
	long lSignature;			// must be 0xDEADBEEF
	BYTE bReceiverAddr;			// receiver ID. 0xff=broadcast
	BYTE bVersion;				// must be 1 for version 1
	long lDataLength;			// size of message
	char bTBD[1];				// to be determined
	BYTE bPattern[4];			// must be 0xaa 0x55 0xaa 0x55
};
