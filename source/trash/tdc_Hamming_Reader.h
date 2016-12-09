#ifndef tdc_Hamming_Reader_H
#define tdc_Hamming_Reader_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Error.h"

/* 
 * tdc_Hamming_Reader 
 */
typedef struct tdc_Hamming_Reader {
	
	char sourcePath[100];
	char *buffer;
		
	int (*read)();

} tdc_Hamming_Reader;

/* 
 * tdc_Hamming_Reader_init 
 */
int tdc_Hamming_Reader_init(tdc_Hamming_Reader *obj);

#endif
