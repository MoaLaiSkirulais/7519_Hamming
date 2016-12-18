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
static int decodeBuffer(tdc_Hamming_Decoder *this, tdc_Hamming_Buffer *buffer) {
	
	/* calcula el tamaño del buffer de salida */
	int newSize = buffer->size / 2 + buffer->size % 2;
	this->outBuffer.bytes = malloc(newSize);
	this->outBuffer.size = newSize;

	tdc_Hamming_Helper h;
	tdc_Hamming_Helper_init(&h);		

	/* loopea el buffer byte a byte */
	unsigned char newByte;
	
	int i;
	for (i = 0; i < buffer->size; i++){

		/* decodea el byte */
		this->input = buffer->bytes[i]; 
		this->decodeByte(this);

		/* cada dos bytes decodeados agrega uno al buffer */
		if (i % 2 == 0){
			newByte = (this->outNibble << 4) & 0b11110000; 
		} else {
			newByte = newByte | this->outNibble;
			memcpy(&this->outBuffer.bytes[i/2], &newByte, 1); 
		}

	}
	
	/* si eran impares los hamming, agrega uno para salvar el ultimo nibble */
	if (i % 2 == 1){		
		newByte = newByte & 0b00001111;
		memcpy(&this->outBuffer.bytes[i/2], &newByte, 1); 
	}

	/* fin */
	// printf("this->outBuffer.size: %d\n", this->outBuffer.size);
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
		0b0000001, /* 1 paridad, descartar */
		0b0000010, /* 2 paridad, descartar */
		0b0000100, /* 3 */
		0b0001000, /* 4 paridad, descartar */
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
	correctedByte = this->input;
	if (this->mode == TDC_HAMMING_DECODER_MODE_CORRECT) {
		correctedByte = swapBit ^ this->input;
	}
	this->output = correctedByte;

	/* extrae el nibble del 7,4 */
	unsigned char bit1 = (correctedByte >> 2) & 0b00000001;
	unsigned char bit234 = (correctedByte >> 3) & 0b00001110;	
	this->outNibble = bit1 | bit234;

	/* analiza una minima estadistica */
	this->stat(this, correctionMask);

	/* end */
	return TDC_HAMMING_OK;
}

/* 
 * stat()
 */
static int stat(tdc_Hamming_Decoder *this, unsigned char *correctionMask) {

	if (correctionMask != 0b00000000){
		this->stats.totalErrors++;
	}
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_Decoder *this) {

	if (this->outBuffer.bytes){
		free(this->outBuffer.bytes);
		this->outBuffer.bytes = NULL;
	}

	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Decoder_init
 */
int tdc_Hamming_Decoder_init(tdc_Hamming_Decoder *obj) {

	obj->outBuffer.bytes = NULL;
	obj->mode = TDC_HAMMING_DECODER_MODE_CORRECT;
	obj->stats.totalErrors = 0;

	obj->destroy = destroy;
	obj->decodeBuffer = decodeBuffer;
	obj->decodeByte = decodeByte;
	obj->stat = stat;

}