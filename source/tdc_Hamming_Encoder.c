#include "tdc_Hamming_Encoder.h"

typedef unsigned char byte;
typedef unsigned char nibble;

/* 
 * encodeBuffer
 */
static int encodeBuffer(tdc_Hamming_Encoder *this, char *buffer) {

	this->outBuffer = realloc(this->outBuffer, strlen(buffer) * 2 + 1);
	printf("strlen(buffer): %lu\n", strlen(buffer)); 
	printf("strlen(buffer): %lu\n", strlen(buffer) * 2 + 1); 
	printf("buffer: %s\n", buffer);

	int i;
	for (i = 0; i < strlen(buffer); i++){
		
		printf("i: %d\n", i); 
		
		unsigned char nible1;
		unsigned char nible2;

		nible1 = (buffer[i] >> 4) & 0b00001111; 
		nible2 = 0b00001111 & buffer[i]; 

		tdc_Hamming_Helper h;
		tdc_Hamming_Helper_init(&h);
		printf("buffer[i]: %c ", buffer[i]); h.printBits(&h, sizeof(buffer[i]), &buffer[i]);

		tdc_Hamming_Encoder encoder;
		tdc_Hamming_Encoder_init(&encoder);
		
		encoder.input = nible1; 
		encoder.encodeByte(&encoder);
		encoder.output = encoder.output | 0b10000000; /* agrega un 1 en el bit no usado para evitar el caracter EOL de C */
		
		memcpy(&this->outBuffer[i*2], &encoder.output, 1); 
		// sprintf(this->outBuffer, "%s%c", this->outBuffer, encoder.output); 
		printf("nible1: "); h.printBits(&h, sizeof(nible1), &nible1);
		printf("\toutput: "); h.printBits(&h, sizeof(encoder.output), &encoder.output);
		this->outBuffer[i*2+1] = '\0'; /* siempre adiciona el EOL para el strlen */
		// printf("this->outBuffer: %s\n", this->outBuffer); 
		printf("strlen(this->outBuffer): %lu\n", strlen(this->outBuffer)); 

		
		
		encoder.input = nible2; 
		encoder.encodeByte(&encoder);		
		encoder.output = encoder.output | 0b10000000; /* agrega un 1 en el bit no usado para evitar el caracter EOL de C */
				
		memcpy(&this->outBuffer[i*2+1], &encoder.output, 1); 
		// sprintf(this->outBuffer, "%s%c", this->outBuffer, encoder.output); 
		encoder.destroy(&encoder);
		printf("nible2: "); h.printBits(&h, sizeof(nible2), &nible2);
		printf("\toutput: "); h.printBits(&h, sizeof(encoder.output), &encoder.output);
		this->outBuffer[i*2+2] = '\0'; /* siempre adiciona el EOL para el strlen */
		// printf("this->outBuffer: %s\n", this->outBuffer); 
		printf("strlen(this->outBuffer): %lu\n", strlen(this->outBuffer)); 

	}

	// printf("strlen(this->outBuffer): %lu\n", strlen(this->outBuffer)); 
	return TDC_HAMMING_OK;

}

/* 
 * encodeByte
 */
static int encodeByte(tdc_Hamming_Encoder *this) {
	
	byte _hammingCalculateParityFast128[256]=
	{

		/*  0  0000	*/ 0b0000000, 
		/*  1  0001	*/ 0b0000111, 
		/*  2  0010	*/ 0b0011001, 
		/*  3  0011	*/ 0b0011110, 
		/*  4  0100	*/ 0b0101010, 
		/*  5  0101	*/ 0b0101101, 
		/*  6  0110	*/ 0b0110011, 
		/*  7  0111	*/ 0b0110100, 
		/*  8  1000	*/ 0b1001011, 
		/*  9  1001	*/ 0b1001100, 
		/* 10  1010	*/ 0b1010010, 
		/* 11  1011	*/ 0b1010101, 
		/* 12  1100	*/ 0b1100001, 
		/* 13  1101	*/ 0b1100110, 
		/* 14  1110	*/ 0b1111000, 
		/* 15  1111	*/ 0b1111111 
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

