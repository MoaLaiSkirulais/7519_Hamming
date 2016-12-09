#ifndef tdc_Hamming_Writer_H
#define tdc_Hamming_Writer_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Error.h"

/* 
 * tdc_Hamming_Writer 
 */
typedef struct tdc_Hamming_Writer {

	char *buffer; 
	int (*write)();

} tdc_Hamming_Writer;

/* 
 * tdc_Hamming_Writer_init 
 */
int tdc_Hamming_Writer_init(tdc_Hamming_Writer *obj);

#endif
