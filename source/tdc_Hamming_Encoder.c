#include "tdc_Hamming_Encoder.h"

typedef unsigned char byte;
typedef unsigned char nibble;

/* 
 * encodeBuffer
 */
static int encodeBuffer(tdc_Hamming_Encoder *this, char *buffer) {

	this->outBuffer = realloc(this->outBuffer, strlen(buffer) * 2 + 1);
	// strcpy(this->outBuffer, "");
	printf("buffer: %s\n", buffer);

	int i;
	for (i = 0; i < strlen(buffer); i++){
		
		// printf("buffer: %c\n", buffer[i]);
		
		char nible1;
		char nible2;

		nible1 = buffer[i] >> 4; 
		nible2 = 0b00001111 & buffer[i]; 

		tdc_Hamming_Helper h;
		tdc_Hamming_Helper_init(&h);

		// printf("%c\n", buffer[i]);
		// printf("\t %d\n", nible2);
		// printf("\t buffer[i]: "); h.printBits(&h, sizeof(buffer[i]), &buffer[i]);
		// printf("\t nible1: "); h.printBits(&h, sizeof(nible1), &nible1);
		// printf("\t nible2: "); h.printBits(&h, sizeof(nible2), &nible2);

		tdc_Hamming_Encoder encoder;
		tdc_Hamming_Encoder_init(&encoder);

		encoder.input = nible1; 
		encoder.encodeByte(&encoder);
		sprintf(this->outBuffer, "%s%c", this->outBuffer, encoder.output); 

		// printf("\t nible1.output: ");
		// h.printBits(&h, sizeof(encoder.output), &encoder.output);

		encoder.input = nible2; 
		encoder.encodeByte(&encoder);
		sprintf(this->outBuffer, "%s%c", this->outBuffer, encoder.output); 
		encoder.destroy(&encoder);

		// printf("\t nible2.output: ");
		// h.printBits(&h, sizeof(encoder.output), &encoder.output);


	}

	return TDC_HAMMING_OK;

}

/* 
 * encodeByte
 */
static int encodeByte(tdc_Hamming_Encoder *this) {
	
	byte _hammingCalculateParityFast128[256]=
	{

		/*  0  0000	*/ 0b0000000, 	/* 0000 */
		/*  1  0001	*/ 0b1110000, 	/* 1000 */
		/*  2  0010	*/ 0b1001100, 	/* 0100 */
		/*  3  0011	*/ 0b0111100, 	/* 1100 */
		/*  4  0100	*/ 0b0101010, 	/* 0010 */
		/*  5  0101	*/ 0b1011010, 	/* 1010 */
		/*  6  0110	*/ 0b1100110, 	/* 0110 */
		/*  7  0111	*/ 0b0010110, 	/* 1110 */
		/*  8  1000	*/ 0b1101001, 	/* 0001 */
		/*  9  1001	*/ 0b0011001, 	/* 1001 */
		/* 10  1010	*/ 0b0100101, 	/* 0101 */
		/* 11  1011	*/ 0b1010101, 	/* 1101 */
		/* 12  1100	*/ 0b1000011, 	/* 0011 */
		/* 13  1101	*/ 0b0110011, 	/* 1011 */
		/* 14  1110	*/ 0b0001111, 	/* 0111 */
		/* 15  1111	*/ 0b1111111    /* 1111 */
	};
	
	this->output = this->input;	

	tdc_Hamming_Helper h;
	tdc_Hamming_Helper_init(&h);

	nibble parity = _hammingCalculateParityFast128[this->input];
	this->output = parity;
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_Encoder *this) {

	free(this->outBuffer);
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Encoder_init
 */
int tdc_Hamming_Encoder_init(tdc_Hamming_Encoder *obj) {
	
	obj->outBuffer = malloc(sizeof(char));
	strcpy(obj->outBuffer, "");

	obj->destroy = destroy;
	obj->encodeBuffer = encodeBuffer;
	obj->encodeByte = encodeByte;
}

