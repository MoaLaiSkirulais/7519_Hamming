#ifndef tdc_Hamming_Decoder_H
#define tdc_Hamming_Decoder_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Encoder.h"
#include "tdc_Hamming_Error.h"
#include "tdc_Hamming_Helper.h"

/* 
 * tdc_Hamming_Decoder_Mode 
 */
typedef enum {

	/* 00 */ TDC_HAMMING_DECODER_MODE_NOCORRECT,
	/* 01 */ TDC_HAMMING_DECODER_MODE_CORRECT /* default */
	
} tdc_Hamming_Decoder_Mode;

/* 
 * tdc_Hamming_Decoder
 */
typedef struct tdc_Hamming_Decoder {
	
	// tdc_Hamming_Encoder_Type type;
	tdc_Hamming_Decoder_Mode mode;
	unsigned char input;
	unsigned char output;
	
	unsigned char outNibble;	
	tdc_Hamming_Buffer outBuffer;
	
	int (*destroy)();
	int (*decodeBuffer)();
	int (*decodeByte)();

} tdc_Hamming_Decoder;

/* 
 * tdc_Hamming_Decoder 
 */
int tdc_Hamming_Decoder_init(tdc_Hamming_Decoder *obj);

#endif
