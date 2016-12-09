#include "tdc_Hamming_Decoder.h"

/* 
 * decodeBuffer
 */
static int decodeBuffer(tdc_Hamming_Encoder *this, char *buffer) {
	
	return TDC_HAMMING_OK;

}

/* 
 * decodeBuffer
 */
static int decodeByte(tdc_Hamming_Decoder *this) {
	
	this->output = this->input;	
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Decoder_init
 */
int tdc_Hamming_Decoder_init(tdc_Hamming_Decoder *obj) {

	obj->decodeBuffer = decodeBuffer;
	obj->decodeByte = decodeByte;
}