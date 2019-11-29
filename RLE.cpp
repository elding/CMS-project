/* RLE.cpp: implementation for RLE compression and decompression functions
 * Author: Sean Berkvens 2019
 */
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define _CRT_SECURE_NO_WARNINGS

int RLECompress(unsigned char* in, int iInLen,
	unsigned char* out, int iOutMax, unsigned char cESC) {

	unsigned char character;  //repeated character
	unsigned char output[10]; //temporary buffer with space for the RLE sequence
	out[0] = '\0';			  //set so we can use strcat()
	int i = 0;                //counter
	int count;				  //number of repeats

	while (i < iInLen) {
		count = 1;				//starts the counter of a set
		while ((in[i] == in[i+1]) && (i < iInLen)) {		//while there are repeated characters, increment the counter
			character = in[i];			//save the repeated character
			count++;
			i++;
		}
		//Encode the output
		if (count >= 3) {
			//RLE encode
			//copy to temp buffer
			sprintf((char*)output, "%c%02x%c", cESC, count, character);
			//copy temp buffer to output buffer
			strcat((char*)out, (char*)output);
		} 
		
		else if (count == 2) {
			//dont encode
			sprintf((char*)output, "%c%c", character, character);
			strcat((char*)out, (char*)output);
		}
		else if (count == 1) {
			output[0] = in[i];
			output[i] = '\0';
			strcat((char*)out, (char*)output);
		
		}
		i++;
	}
	return(strlen((char*)out));
}

//int RLEDecompress(unsigned char* in, int iInLen,
//	unsigned char* out, int iOutMax, unsigned char cESC) {
//
//	int j = 0;
//	unsigned char output2[10];
//	unsigned char character2;
//	out[0] = '\0';
//	char charOut;
//	int totalcharCount = 0;
//	
//	for (j = 0; j < iInLen - 1; j++) {
//
//		if (in[j] == cESC) {
//			totalcharCount += ((int)(in[j + 1]) - 48) + ((int)(in[j + 2]) - 48);
//		}
//	}
//
//	/*char *seqOut;
//	seqOut = (char*)malloc(totalcharCount * sizeof(char));
//	printf("\n%d",totalcharCount);*/
//
//	int charAmnt = 0;
//	for (j = 0; j < (iInLen-1); j++) {
//		if (in[j] == cESC) {
//			charAmnt = ((int)(in[j + 1]) - 48) + ((int)(in[j + 2]) - 48);
//			charOut = in[j + 3];
//			
//			////seqOut needs to be the charOut times the charAmnt
//			//for (int n = 0; n < charAmnt; n++) {
//			//	seqOut[n] = charOut;
//			//}
//
//			sprintf((char*)output2, "%c*%d", charOut,charAmnt);
//			strcat((char*)out, (char*)output2);
//		}
//	}
//	return(strlen((char*)out));
//}

