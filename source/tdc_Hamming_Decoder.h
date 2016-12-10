#ifndef tdc_Hamming_Decoder_H
#define tdc_Hamming_Decoder_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Encoder.h"
#include "tdc_Hamming_Error.h"
#include "tdc_Hamming_Helper.h"

/* 
 * tdc_Hamming_Decoder
 */
typedef struct tdc_Hamming_Decoder {
	
	tdc_Hamming_Encoder_Type type;
	char input;
	char output;
	
	unsigned char outNibble;
	
	unsigned char *outBuffer; 
	
	int (*destroy)();
	int (*decodeBuffer)();
	int (*decodeByte)();

} tdc_Hamming_Decoder;

/* 
 * tdc_Hamming_Decoder 
 */
int tdc_Hamming_Decoder_init(tdc_Hamming_Decoder *obj);

#endif
