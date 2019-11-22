/*
 *  Implementation: Functions for File IO - Getting random messages from a file
 *  by Tyler Boire, Sean Berkvens, Alex Da Silva, 2019
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>			// Dynamic memory allocation for arrays that store quote location and length
#include "message.h"
#include <errno.h>
#include "Queues.h"

/* 
 *  Function gets a random number between min and max (max is the number of quotes in the file)
 */

 int frandNum(int min, int max) {
	return(min + (rand() % (max - min + 1)));
}

/*
 *  Function returns number of quotes in the file (only need to run once)
 */

int fnumQuotes(void) {			//if you read one %, step forward again and if another % write file index
	FILE* fp;
	errno_t err;
	char c;
	int counter = 0;

	if (err = fopen_s(&fp, "FortuneCookies.txt", "r") == 0) {
		printf("\nFile opened successfully\n");

		//Read file one character at a time

		while ((c = fgetc(fp)) != EOF) {
			if (c == '%') {
				if (fgetc(fp) == '%') {
					counter++;				//increments the number of quotes
				}
			}
		}
		fclose(fp);
		printf("\nNumber of quotes:  %d\n", counter);	// Print out all the number of quotes
		return(counter);
	}
	else {												// Else if statement if the file failed to open
		printf("\nFailed to open File\n");
		fclose(fp);
		return 1;
	}
}

/*
 *  Function returns an array that indicates the start of every quote in the file (number of characters from the start of the file) 
 */

long int* fquoteIndices(int numQuotes) {
	FILE* fp;
	errno_t err;
	char c;
	long numChars = 0;	// counts where the quote starts
	int index = 0;		// counter for the amount of indicies

	long* quoteIndices = (long*)malloc(numQuotes * sizeof(long));		// Allocates memory for an array to store that data for quoteIndicies

	if (err = fopen_s(&fp, "FortuneCookies.txt", "r") == 0) {

		//Read file one character at a time

		while ((c = fgetc(fp)) != EOF) {
			
			if (c == '%') {
				numChars++;
				if (fgetc(fp) == '%') {
					fgetc(fp);
					quoteIndices[index] = ftell(fp);		// Puts the file pointer to the quote indicies
					index++;								// Increments the counter for indicies
				}
			}
			numChars++;
		}
		fclose(fp);
		return(quoteIndices);
	}
}

/* 
 *  Function returns the smaller of the actual quote length or MAX_QUOTE_LENGTH
 */

 int* fquoteLength(int numQuotes, long int* quoteIndices) {
	int* quoteLengths = (int*)malloc(numQuotes * sizeof(int));					// Allocates memory for an array of quotelengths
	int lastQuoteLength = 0;														// A temporary incrementor
	FILE* fp;
	for (int i = 0; i < numQuotes; i++) {										// For loop that will cut all quotes longer than MAX_QUOTE_LENGTH (140) to 140 characters
		quoteLengths[i] = ((int)quoteIndices[i + 1] - (int)quoteIndices[i] - 2);
		if (quoteLengths[i] > MAX_QUOTE_LENGTH) {
			quoteLengths[i] = MAX_QUOTE_LENGTH;
		}
	}

	if (fopen_s(&fp, "FortuneCookies.txt", "r") == 0) {							// If loop obtains the length of the last quote
		fseek(fp, quoteIndices[numQuotes - 1], SEEK_SET);
		while (fgetc(fp) != EOF) {
			lastQuoteLength++;
		}
	}
	quoteLengths[numQuotes - 1] = lastQuoteLength;								// numQuotes must be subtracted by 1 due to the fact our algorithm breaks with the last quote
	fclose(fp);
	return(quoteLengths);
}

/*
 *  Function that gets a random quote from the FortuneCookies file
 */ 

int GetMessageFromFile(char* buff, int iLen, int randNum, int numQuotes, long int* quoteIndices, int* quoteLengths) {
	FILE* fp;
	errno_t err;
	int g = randNum;				// Set g to randNum to obtain the quote at the random number index
	int i = 0;
	char holder;
	if (err = fopen_s(&fp, "FortuneCookies.txt", "r") == 0) {				// If loop that opens the file and looks for the quoteindicies at the random number location
		fseek(fp, quoteIndices[g], SEEK_SET);
		while ((holder = (char)fgetc(fp)) != '%' && i < quoteLengths[g]){	// While loop that will copy the contents of the quote at the index into a buffer 
			buff[i] = holder;
			i++;
		}
		buff[i] = '\0';														
		fclose(fp);
	}
	return(0);
}