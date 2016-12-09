#ifndef tdc_Hamming_Encoder_H
#define tdc_Hamming_Encoder_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Helper.h"
#include "tdc_Hamming_Error.h"

/* 
 * tdc_Hamming_Encoder_Type 
 */
typedef enum {

	TDC_HAMMING_ENCODER_TYPE_74,
	TDC_HAMMING_ENCODER_TYPE_1511
	
} tdc_Hamming_Encoder_Type;

/* 
 * tdc_Hamming_Encoder 
 */
typedef struct tdc_Hamming_Encoder {
	
	tdc_Hamming_Encoder_Type type;
	char input;
	char output;
	
	int (*encodeBuffer)();
	int (*encodeByte)();

} tdc_Hamming_Encoder;

/* 
 * tdc_Hamming_Encoder 
 */
int tdc_Hamming_Encoder_init(tdc_Hamming_Encoder *obj);

#endif
