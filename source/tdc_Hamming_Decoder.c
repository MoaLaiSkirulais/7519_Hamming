#include "tdc_Hamming_Decoder.h"

unsigned char SumBitsModulo2(unsigned char bits){

    unsigned char sum, mask;
    sum = 0;

    for (mask = 0x01; mask < (0x01 << 7); mask <<=1 ) {
        if (bits & mask) {
            sum++;
        }
    }

    return (sum & 0x01);
}

/* 
 * decodeBuffer
 */
static int decodeBuffer(tdc_Hamming_Encoder *this, char *buffer) {
	
	/* calcula el tamaño del buffer de salida 
	 p/ej si son 10 bytes entonces seran 5 bytes
	 p/ej si son 11 bytes  entonces seran 6 bytes y completa con 0000 */

	int newSize = strlen(buffer) / 2 + strlen(buffer) % 2;
	// printf("newSize: %d\n", newSize);
	this->outBuffer = realloc(this->outBuffer, newSize + 1);
	// strcpy(this->outBuffer, ""); 

	tdc_Hamming_Helper h;
	tdc_Hamming_Helper_init(&h);		

	/* loopea el buffer byte a byte */
	unsigned char newByte;
	
	int i;
	for (i = 0; i < strlen(buffer); i++){

		/* decodea el byte */
		tdc_Hamming_Decoder decoder;
		tdc_Hamming_Decoder_init(&decoder);

		decoder.input = buffer[i]; 
		decoder.decodeByte(&decoder);

		/* cada dos bytes decodeados agrega uno al buffer */
		if (i % 2 == 0){
			newByte = (decoder.outNibble << 4) & 0b11110000; 
		} else {
			newByte = newByte | decoder.outNibble;
			memcpy(&this->outBuffer[i/2], &newByte, 1); 
			this->outBuffer[i/2+1] = '\0'; /* siempre adiciona el EOL para el strlen */
		}

		decoder.destroy(&decoder);
	}
	
	/* si eran impares los hamming, agrega uno para salvar el ultimo nibble */
	if (i % 2 == 1){		
		newByte = newByte & 0b00001111;
		memcpy(&this->outBuffer[i/2], &newByte, 1); 
		this->outBuffer[i/2+1] = '\0'; /* siempre adiciona el EOL para el strlen */
	}

	/* fin */
	// printf("strlen(this->outBuffer): %lu\n", strlen(this->outBuffer)); 
	// printf("this->outBuffer: %s\n", this->outBuffer); 
	return TDC_HAMMING_OK;

}

/* 
 * decodeByte
 */
static int decodeByte(tdc_Hamming_Decoder *this) {
	
	/* flip bit */
	const unsigned char swapBitTable[8]=
	{
		0b0000000, /* 0 */
		0b0000001, /* 1 no tiene sentido */
		0b0000010, /* 2 no tiene sentido */
		0b0000100, /* 3 */
		0b0001000, /* 4 no tiene sentido */
		0b0010000, /* 5 */
		0b0100000, /* 6 */
		0b1000000  /* 7 */	
	};

	/* tool para impresion */
	tdc_Hamming_Helper h;
	tdc_Hamming_Helper_init(&h);

	unsigned char correctionMask = 0b00000000;

	/* paridad 1 */
	unsigned char p1;
	p1 = this->input & 0b1010101;
	if (SumBitsModulo2(p1) == 1){
		correctionMask = correctionMask | 0b00000001;
	};

	/* paridad 2 */
	unsigned char p2;
	p2 = this->input & 0b1100110;
	if (SumBitsModulo2(p2) == 1){
		correctionMask = correctionMask | 0b00000010;
	};

	/* paridad 3 */
	unsigned char p3;
	p3 = this->input & 0b1111000;
	if (SumBitsModulo2(p3) == 1){
		correctionMask = correctionMask | 0b00000100;
	};

	/* obtiene bit invalido que debe flipearse */
	unsigned char swapBit;
	swapBit = swapBitTable[correctionMask];

	/* flip / correct */
	unsigned char correctedByte;
	correctedByte = swapBit ^ this->input;
	this->output = correctedByte;

	/* extrae el nibble del 7,4 */
	unsigned char bit1 = (correctedByte >> 2) & 0b00000001;
	unsigned char bit234 = (correctedByte >> 3) & 0b00001110;	
	this->outNibble = bit1 | bit234;

	/* end */
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_Decoder *this) {

	free(this->outBuffer);
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Decoder_init
 */
int tdc_Hamming_Decoder_init(tdc_Hamming_Decoder *obj) {

	obj->outBuffer = malloc(sizeof(char));
	strcpy(obj->outBuffer, "");

	obj->destroy = destroy;
	obj->decodeBuffer = decodeBuffer;
	obj->decodeByte = decodeByte;
}