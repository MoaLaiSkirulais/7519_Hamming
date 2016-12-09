#include "tdc_Hamming_Encoder.h"

/* 
 * encodeBuffer
 */
static int encodeBuffer(tdc_Hamming_Encoder *this, char *buffer) {
	
	// printf("file.inBuffer: %s\n", buffer);
	return TDC_HAMMING_OK;

}

/* 
 * encodeByte
 */
static int encodeByte(tdc_Hamming_Encoder *this) {
	
	this->output = this->input;
	
	char a = 0b1110;
	char b = 0b0001;
	
	// p1 = 1,2,4 || 3,5,7
	// p1 = 1,2,4
	char p1 = b ^ 0b0001 /*d3*/ ^ 0b0010 /*d5*/ ^ 0b1000 /*d7*/;
	char p2 = b ^ 0b0001 /*d3*/ ^ 0b0100 /*d6*/ ^ 0b1000 /*d7*/;
	char p4 = b ^ 0b0010 /*d5*/ ^ 0b0100 /*d6*/ ^ 0b1000 /*d7*/;
	
	// printf("a: %d\n", a);
	// printf("b: %d\n", b);
	// printf("b: %d\n", b);
	// printf("p1: %d\n", p1);
	// printf("p2: %d\n", p2);
	// printf("p4: %d\n", p4);
	// printBits(sizeof(p1), &p1);
	
	// tdc_Hamming_Helper h;
	// tdc_Hamming_Helper_init(&h);

	// h.printBits(&h, sizeof(b), &b);
	// h.printBits(&h, sizeof(p1), &p1);
	// h.printBits(&h, sizeof(p2), &p2);
	// h.printBits(&h, sizeof(p4), &p4);
	
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Encoder_init
 */
int tdc_Hamming_Encoder_init(tdc_Hamming_Encoder *obj) {

	obj->encodeBuffer = encodeBuffer;
	obj->encodeByte = encodeByte;
}