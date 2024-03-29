#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "message.h"
#include "Queues.h"
#include "sound.h"
#include <Windows.h>  // Includes the functions for serial communication via RS232
#include <stdlib.h>
#include "RS232Comm.h"
#include "RLE.h"

#define EX_FATAL 1
#define BUFSIZE 140
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

char AudioBuff[960000];

char* COMPORT;
extern HANDLE hCom;

union convert {
	Frame frame;
	char buffer[sizeof(Frame)];
}converter;

union shortToChar {
	char chr[960000];
	short shrt[480000];
}shortToChar;



extern short iBigBuf[];												// buffer
extern long  lBigBufSize;											// total number of samples
short* iBigBufNew = (short*)malloc(lBigBufSize * sizeof(short));		// buffer used for reading recorded sound from file

char save;
char replay;
char c;																// used to flush extra input
FILE* f;






int MainMenu(void) {

	int input;
	int Condition = 1;

	printf("\n \n*************Welcome to the Main Menu************** \n \n \n");
	printf("Please select an option. Press the corrosponding number for the selection \n \n ");
	printf("1: Sound \n 2: Queuing \n 3: Phonebook \n 4: Testing \n 0: Exit \n \n");

	scanf_s("\n \n %d", &input);


	if (input == 0) {
		return 0;  // Terminates the program
	}
	else if (input > 4 || input < 0) {
		printf("Please enter a valid input \n");
		scanf_s("\n %d", &input);
	}

	switch (input) {
	case 1:
		if (input == 1) {
			Sound();
		}
		break;

	case 2:
		if (input == 2) {
			Queueing();
		}
		break;

	case 3:
		if (input == 3) {
			Phonebook();
		}
		break;

	case 4:
		if (input == 4) {
			Testing();
		}
		break;
	}

}


void Sound(void) {

	int SubInput;

	printf("\n\n *******************Welcome to the Sound SubMenu******************* \n \n ");
	printf("Please select and option. Press the corrosponding number for the selection \n \n");
	printf("1: Recording Audio \n 2: Playback \n 3: Sound Settings \n 0: Return to main menu \n");

	scanf_s("\n \n %d", &SubInput);

	if (SubInput == 0) {
		MainMenu();
	}
	else if (SubInput > 3 || SubInput < 0) {
		printf("Please enter a valid input \n");
		scanf_s("\n %d", &SubInput);
	}

	switch (SubInput) {
	case 1:
		if (SubInput == 1) {
			RecordAudio();
		}
		break;
	case 2:
		if (SubInput == 2) {
			Playback();
		}
		break;

	case 3:
		if (SubInput == 3) {
			SoundSettings();
		}
		break;
	}
	MainMenu();
}


void Queueing(void) {

	int SubInput;

	printf("\n\n *******************Welcome to the Queueing SubMenu******************* \n \n ");
	printf("Please select and option. Press the corrosponding number for the selection \n \n");
	printf("1: Record a message \n 2: Delete Message \n 3: Send Message \n 0: Return to main menu \n \n \n");

	scanf_s("\n %d", &SubInput);

	if (SubInput == 0) {
		MainMenu();
	}
	else if (SubInput > 3 || SubInput < 0) {
		printf("Please enter a valid input \n");
		scanf_s("\n %d", &SubInput);
	}
	else {
		switch (SubInput) {
		case 1:
			if (SubInput == 1) {
				return RecordText();
			}
			break;
		case 2:
			if (SubInput == 2) {
				return DeleteText();
			}
			break;

		case 3:
			if (SubInput == 3) {
				return SendText();
			}
			break;
		}
	}
	MainMenu();
}



void Phonebook(void) {

	int SubInput;

	printf("\n\n *******************Welcome to the Phonebook******************* \n \n ");
	printf("Please select and option. Press the corrosponding number for the selection \n \n");
	printf("1: Display Current address \n 2: Change receiver ID \n 0: Return to main menu \n \n");

	scanf_s("\n \n %d", &SubInput);

	if (SubInput == 0) {
		MainMenu();
	}

	switch (SubInput) {
	case 1:
		if (SubInput == 1) {
			DisplayAddress();
		}
		break;
	case 2:
		if (SubInput == 2) {
			ChangeAddress();
		}
		break;

	}
	MainMenu();
}



void Testing(void) {

	int SubInput;

	printf("\n\n *******************Welcome to the Debug Menu******************* \n \n ");
	printf("Please select and option. Press the corrosponding number for the selection \n \n");
	printf("1: Test recording functionality \n 2: Test Audio Playback \n 3: Test RS232 Text communication \n 0: Return to main menu \n");

	scanf_s("\n %d", &SubInput);

	if (SubInput == 0) {
		MainMenu();
	}

	switch (SubInput) {
	case 1:
		if (SubInput == 1) {
			TransmitMessage();
		}
		break;
	case 2:
		if (SubInput == 2) {
			Playback();
		}
		break;
	case 3:
		if (SubInput == 3) {
			TestRS232();
		}
		break;

	}
	MainMenu();
}

void TestRS232(void) {
	int Switcher;

	printf("Please indicate if sender or receiver. 1 for sender, 0 for receiver");
	scanf_s("%d", &Switcher);
	//COMPORT = "COM4";
	COMPORT = (char*)malloc(10 * sizeof(char));
	printf("%d", Switcher);

	if (Switcher == 1) {
		//COMPORT[0] = "COM4";
		COMPORT = (char*)"COM10";

		char msgOut[1024];// Sent message							// Received message
		printf("Type something to send\n");
		initPort();
		getchar();
		fgets(msgOut, 1024, stdin);
		outputToPort(msgOut, strlen(msgOut) + 1);			// Send string to port - include space for '\0' termination
		Sleep(1000);									// Allow time for signal propagation on cable
		return;
	}

	else if (Switcher == 0) {
		COMPORT = (char*)"COM10";
		initPort();
		// Receiver program - comment out these 3 lines if sender - Start receiver first
		char msgIn[BUFSIZE];
		inputFromPort(msgIn, BUFSIZE);					// Receive string from port
		printf("\nMessage Received: %s\n\n", msgIn);	// Display message from port


		purgePort();									// Purge the port
		CloseHandle(hCom);								// Closes the handle pointing to the COM port
		system("pause");
	}



}

char* RecordAudio(void) {


	InitializePlayback();
	InitializeRecording();

	// start recording
	RecordBuffer(iBigBuf, lBigBufSize);
	CloseRecording();

	// playback recording 
	printf("\nPlaying recording from buffer\n");
	PlayBuffer(iBigBuf, lBigBufSize);
	ClosePlayback();

	memcpy_s(shortToChar.shrt, sizeof(shortToChar.shrt), iBigBuf, lBigBufSize * 2);

	// save audio recording  
	printf("Would you like to save your audio recording? (y/n): ");
	scanf_s("%c", &save, 1);
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((save == 'y') || (save == 'Y')) {
		/* Open input file */
		fopen_s(&f, "C:\\Users\\boire\\Desktop\\ahhhh\recording.dat", "wb");
		if (!f) {
			printf("unable to open %s\n", "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat");
			return AudioBuff;
		}
		printf("Writing to sound file ...\n");
		fwrite(iBigBuf, sizeof(short), lBigBufSize, f);
		fclose(f);
	}

	// replay audio recording from file -- read and store in buffer, then use playback() to play it
	printf("Would you like to replay the saved audio recording from the file? (y/n): ");
	scanf_s("%c", &replay, 1);
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((replay == 'y') || (replay == 'Y')) {
		/* Open input file */
		fopen_s(&f, "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat", "rb");
		if (!f) {
			printf("unable to open %s\n", "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat");
			return AudioBuff;
		}
		printf("Reading from sound file ...\n");
		fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
		fclose(f);
	}
	InitializePlayback();
	printf("\nPlaying recording from saved file ...\n");
	PlayBuffer(iBigBufNew, lBigBufSize);
	ClosePlayback();

	memcpy_s(AudioBuff, sizeof(AudioBuff), iBigBuf, lBigBufSize * 2);


	printf("\n");
	system("pause");
	return shortToChar.chr;
	
	
}

int Playback(void) {
	COMPORT = (char*)"COM5";
	union shortToChar shortToChar2;
	
	initPort();
	

	inputFromPort(shortToChar2.chr, sizeof(shortToChar2.chr));



	InitializePlayback();
	printf("\nPlaying recording from saved file ...\n");
	PlayBuffer(shortToChar2.shrt, sizeof(shortToChar2.chr)/2);
	ClosePlayback();

	printf("\n");
	system("pause");
	return 1; 
	




}

void SoundSettings(void) {

	printf("Not implemented yet");
	return; 



}



void DisplayAddress(void) {
	return;
}

void RecordText(void) {
	COMPORT = (char*)"COM5";
	int MessNum;
	initPort();
	char p[10];

	char msgIn[sizeof(Frame) + 1];
	inputFromPort(msgIn, BUFSIZE);
	MessNum = atoi(msgIn);

	printf("ready to continue? y/n \n");
	scanf("%s", p);


	link receive;

	InitQueue();

	for (int j = 0; j < MessNum; j++) {
		receive = (link)malloc(sizeof(node)); // initialize queue memory


		inputFromPort(msgIn, sizeof(converter.buffer) );

		//memcpy(receive->Data.message, msgIn, BUFSIZE);

		memcpy(converter.buffer, msgIn, sizeof(msgIn) );

		
		printf("Message: %s\n", converter.frame.r.message);

		receive->frame = converter.frame;

		AddToQueue(receive);  // queue up messages with user input
	}


	link output;

	while ((output = DeQueue()) != NULL) {
		converter.frame = output->frame;
		printf("\nFrame from queue:");
		printf("Message: %s\n", converter.frame.r.message);
		Sleep(1000);									// Allow time for signal propagation on cable
		free(output);
	}

	return;

}

void DeleteText(void) {
	return;
}

void SendText(void) {

	int i;
	link node;

	printf("How many messages?\n ");
	scanf_s("%d", &i);
	link temp;
	char NumMessage[8];

	char p[10];

	InitQueue();
	char msgOut[140];// Sent message	

	itoa(i, NumMessage, 10); // number of messages we are going to send



	COMPORT = (char*)malloc(10 * sizeof(char));

	COMPORT = (char*)"COM5";
	initPort();
	outputToPort(NumMessage, 2);

	printf("ready to continue? y/n \n");
	scanf("%s", p);

	getchar();

	for (int j = 0; j < i; j++) {
		Frame holder = { NULL, NULL };

		Header head = { 0,0,0,0};
		item message = { 0,0,0 };
		//message.message = msgOut;
		head.isAudio = 0;


		temp = (link)malloc(sizeof(Node));

		memset(msgOut, 0, 140);

		//getchar();					
		printf("Type something to send\n");
		fgets(msgOut, 140, stdin);
		printf("\n\n%s\n\n", msgOut);
		fflush(stdin);

		memcpy(message.message, msgOut, BUFSIZE);
		//strcpy(temp->Frame.message, msgOut);
		holder.h = head;
		holder.r = message;
		temp->frame = holder;

		AddToQueue(temp);  // queue up messages with user input
	}



	while ((node = DeQueue()) != NULL) {

		converter.frame = node->frame;

		outputToPort(converter.buffer, sizeof(converter.buffer) + 1);			// Send string to port - include space for '\0' termination
		Sleep(1000);									// Allow time for signal propagation on cable
		free(node);
	};
	MainMenu();
}

void ChangeAddress(void) {
	return;

}

int TestRecord(void) {
	// initialize playback and recording
	InitializePlayback();
	InitializeRecording();

	// start recording
	RecordBuffer(iBigBuf, lBigBufSize);
	CloseRecording();

	// playback recording 
	printf("\nPlaying recording from buffer\n");
	PlayBuffer(iBigBuf, lBigBufSize);
	ClosePlayback();

	// save audio recording  
	printf("Would you like to save your audio recording? (y/n): ");
	scanf_s("%c", &save, 1);
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((save == 'y') || (save == 'Y')) {
		/* Open input file */
		fopen_s(&f, "C:\\Users\\boire\\Desktop\\ahhhh\recording.dat", "wb");
		if (!f) {
			printf("unable to open %s\n", "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat");
			return 1;
		}
		printf("Writing to sound file ...\n");
		fwrite(iBigBuf, sizeof(short), lBigBufSize, f);
		fclose(f);
	}

	// replay audio recording from file -- read and store in buffer, then use playback() to play it
	printf("Would you like to replay the saved audio recording from the file? (y/n): ");
	scanf_s("%c", &replay, 1);
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((replay == 'y') || (replay == 'Y')) {
		/* Open input file */
		fopen_s(&f, "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat", "rb");
		if (!f) {
			printf("unable to open %s\n", "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat");
			return 1;
		}
		printf("Reading from sound file ...\n");
		fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
		fclose(f);
	}
	InitializePlayback();
	printf("\nPlaying recording from saved file ...\n");
	PlayBuffer(iBigBufNew, lBigBufSize);
	ClosePlayback();



	printf("\n");
	system("pause");
	return 1;


}
int TestPlayback(void) {
	// replay audio recording from file -- read and store in buffer, then use playback() to play it
	printf("Would you like to replay the saved audio recording from the file? (y/n): ");
	scanf_s("%c", &replay, 1);
	while ((c = getchar()) != '\n' && c != EOF) {}								// Flush other input
	if ((replay == 'y') || (replay == 'Y')) {
		/* Open input file */
		fopen_s(&f, "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat", "rb");
		if (!f) {
			printf("unable to open %s\n", "C:\\Users\\boire\\Desktop\\ahhhh\\recording.dat");
			return 1;
		}
		printf("Reading from sound file ...\n");
		fread(iBigBufNew, sizeof(short), lBigBufSize, f);				// Record to new buffer iBigBufNew
		fclose(f);
	}
	InitializePlayback();
	printf("\nPlaying recording from saved file ...\n");
	PlayBuffer(iBigBufNew, lBigBufSize);
	ClosePlayback();

	printf("\n");
	system("pause");
	return 1;
}



void TransmitMessage(void) {

	int i;
	printf("Please press 1 for audio message, 2 for text message \n");
	char AudioMess[200000];

	scanf_s("%d", &i);

	if (i == 1) {

		memcpy_s(shortToChar.chr, sizeof(shortToChar.chr), RecordAudio(), 20000);

		Frame holder = { NULL, NULL };  // create a message frame with header and payload

		Header head = { 0,0,0,0 }; // Sender id, receiver id, priority value, audio flag
		item message = { 0,0}; // text or audio message. Can be both, implement later

		holder.h = head;
		holder.r = message;
		//message.message = msgOut;

		head.isAudio = 1;
		//RLECompress(AudioMess, sizeof(AudioMess), (unsigned char*)message.later, sizeof(message.later), '%'); // compress items into a buffer, right now is same size as original

		memcpy_s(message.later, sizeof(message.later), shortToChar.chr, sizeof(shortToChar.chr));

		converter.frame = holder;

		COMPORT = (char*)malloc(10 * sizeof(char));

		COMPORT = (char*)"COM5";
		
		/*InitializePlayback();

		PlayBuffer(shortToChar.shrt, sizeof(shortToChar.shrt)/2 );

		ClosePlayback();*/

		memcpy(converter.buffer, shortToChar.chr, sizeof(shortToChar.chr));

		initPort();

		outputToPort(converter.buffer, sizeof(converter.buffer) + 1);			// Send audio message over RS232 cable
		Sleep(1000);									// Allow time for signal propagation on cable


		purgePort();
		CloseHandle(hCom);
		
	}
	else if (i == 2) {

		SendText(); // call the send text function. Can transmit any number of text messages
	}



}

