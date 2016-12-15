#ifndef tdc_Hamming_Buffer_H
#define tdc_Hamming_Buffer_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * tdc_Hamming_Encoder 
 */
typedef struct tdc_Hamming_Buffer {
	
	unsigned char *bytes; 
	// char byte[4]; 
	int size; 

} tdc_Hamming_Buffer;


#endif
