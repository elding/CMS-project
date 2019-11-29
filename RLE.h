/* RLE.h: interface for RLE compression and decompression functions
 * Author: Sean Berkvens 2019
 */

//prototypes
int RLECompress(unsigned char* in, int iInLen, 
	unsigned char*out, int iOutMax, unsigned char cESC);

int RLEDecompress(unsigned char* in, int iInLen,
	unsigned char* out, int iOutMax, unsigned char cESC);

#pragma once
