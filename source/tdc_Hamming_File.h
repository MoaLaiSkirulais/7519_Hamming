#ifndef tdc_Hamming_File_H
#define tdc_Hamming_File_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Buffer.h"
#include "tdc_Hamming_Error.h"

/* 
 * tdc_Hamming_File 
 */
typedef struct tdc_Hamming_File {

	char inPath[100];
	char outPath[100];
	
	tdc_Hamming_Buffer inBuffer; 
	tdc_Hamming_Buffer outBuffer; /* es medio confuso dos buffers, deberia alcanzar con uno */
	
	int size;
	
	int (*destroy)();
	int (*read)();
	int (*write)();

} tdc_Hamming_File;

/* 
 * tdc_Hamming_File_init 
 */
int tdc_Hamming_File_init(tdc_Hamming_File *obj);

#endif
