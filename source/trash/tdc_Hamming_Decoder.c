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
	
	return TDC_HAMMING_OK;

}

/* 
 * decodeByte
 */
static int decodeByte(tdc_Hamming_Decoder *this) {
	
	/* table convering encoded value (with error) to original data */
	/* hammingDecodeValues[code] = original data */
	// const unsigned char hammingDecodeValues[CODE_VALUES] =
	const unsigned char hexaHammingDecodeValues[128] =
	{
		0x00, 0x00, 0x00, 0x03, 0x00, 0x05, 0x0E, 0x07,     /* 0x00 to 0x07 */
		0x00, 0x09, 0x0E, 0x0B, 0x0E, 0x0D, 0x0E, 0x0E,     /* 0x08 to 0x0F */
		0x00, 0x03, 0x03, 0x03, 0x04, 0x0D, 0x06, 0x03,     /* 0x10 to 0x17 */
		0x08, 0x0D, 0x0A, 0x03, 0x0D, 0x0D, 0x0E, 0x0D,     /* 0x18 to 0x1F */
		0x00, 0x05, 0x02, 0x0B, 0x05, 0x05, 0x06, 0x05,     /* 0x20 to 0x27 */
		0x08, 0x0B, 0x0B, 0x0B, 0x0C, 0x05, 0x0E, 0x0B,     /* 0x28 to 0x2F */
		0x08, 0x01, 0x06, 0x03, 0x06, 0x05, 0x06, 0x06,     /* 0x30 to 0x37 */
		0x08, 0x08, 0x08, 0x0B, 0x08, 0x0D, 0x06, 0x0F,     /* 0x38 to 0x3F */
		0x00, 0x09, 0x02, 0x07, 0x04, 0x07, 0x07, 0x07,     /* 0x40 to 0x47 */
		0x09, 0x09, 0x0A, 0x09, 0x0C, 0x09, 0x0E, 0x07,     /* 0x48 to 0x4F */
		0x04, 0x01, 0x0A, 0x03, 0x04, 0x04, 0x04, 0x07,     /* 0x50 to 0x57 */
		0x0A, 0x09, 0x0A, 0x0A, 0x04, 0x0D, 0x0A, 0x0F,     /* 0x58 to 0x5F */
		0x02, 0x01, 0x02, 0x02, 0x0C, 0x05, 0x02, 0x07,     /* 0x60 to 0x67 */
		0x0C, 0x09, 0x02, 0x0B, 0x0C, 0x0C, 0x0C, 0x0F,     /* 0x68 to 0x6F */
		0x01, 0x01, 0x02, 0x01, 0x04, 0x01, 0x06, 0x0F,     /* 0x70 to 0x77 */
		0x08, 0x01, 0x0A, 0x0F, 0x0C, 0x0F, 0x0F, 0x0F      /* 0x78 to 0x7F */
	};

	const unsigned char hammingDecodeValues[128] =
	{
		0b0000, 0b0000, 0b0000, 0b0011, 0b0000, 0b0101, 0b1110, 0b0111, /* 00 - */
		0b0000, 0b1001, 0b1110, 0b1011, 0b1110, 0b1101, 0b1110, 0b1110, /* 08 - */
		0b0000, 0b0011, 0b0011, 0b0011, 0b0100, 0b1101, 0b0110, 0b0011, /* 16 - */
		0b1000, 0b1101, 0b1010, 0b0011, 0b1101, 0b1101, 0b1110, 0b1101, /* 24 - */
		0b0000, 0b0101, 0b0010, 0b1011, 0b0101, 0b0101, 0b0110, 0b0101, /* 32 - */
		0b1000, 0b1011, 0b1011, 0b1011, 0b1100, 0b0101, 0b1110, 0b1011, /* 40 - */
		0b1000, 0b0001, 0b0110, 0b0011, 0b0110, 0b0101, 0b0110, 0b0110, /* 48 - */
		0b1000, 0b1000, 0b1000, 0b1011, 0b1000, 0b1101, 0b0110, 0b1111, /* 56 - */
		0b0000, 0b1001, 0b0010, 0b0111, 0b0100, 0b0111, 0b0111, 0b0111, /* 64 - */
		0b1001, 0b1001, 0b1010, 0b1001, 0b1100, 0b1001, 0b1110, 0b0111, /* 72 - */
		0b0100, 0b0001, 0b1010, 0b0011, 0b0100, 0b0100, 0b0100, 0b0111, /* 80 - */
		0b1010, 0b1001, 0b1010, 0b1010, 0b0100, 0b1101, 0b1010, 0b1111, /* 88 - */
		0b0010, 0b0001, 0b0010, 0b0010, 0b1100, 0b0101, 0b0010, 0b0111, /* 96 - */
		0b1100, 0b1001, 0b0010, 0b1011, 0b1100, 0b1100, 0b1100, 0b1111, /* 104 - */
		0b0001, 0b0001, 0b0010, 0b0001, 0b0100, 0b0001, 0b0110, 0b1111, /* 112 - */
		0b1000, 0b0001, 0b1010, 0b1111, 0b1100, 0b1111, 0b1111, 0b1111  /* 120 - 127 */
	};
	
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

	tdc_Hamming_Helper h;
	tdc_Hamming_Helper_init(&h);
	printf("this->input: "); h.printBits(&h, sizeof(this->input), &this->input);

	unsigned char correctionMask = 0b00000000;
	
	unsigned char p1;
	p1 = this->input & 0b1010101;
	printf("p1: "); h.printBits(&h, sizeof(p1), &p1);
	printf("SumBitsModulo2(p1): %d\n", SumBitsModulo2(p1));
	if (SumBitsModulo2(p1) == 1){
		printf("error en p1\n");
		correctionMask = correctionMask | 0b00000001;
	};

	unsigned char p2;
	p2 = this->input & 0b1100110;
	printf("p2: "); h.printBits(&h, sizeof(p2), &p2);
	printf("SumBitsModulo2(p2): %d\n", SumBitsModulo2(p2));
	if (SumBitsModulo2(p2) == 1){
		printf("error en p2\n");
		correctionMask = correctionMask | 0b00000010;
	};

	unsigned char p3;
	p3 = this->input & 0b1111000;
	printf("p3: "); h.printBits(&h, sizeof(p3), &p3);
	printf("SumBitsModulo2(p3): %d\n", SumBitsModulo2(p3));
	if (SumBitsModulo2(p3) == 1){
		printf("error en p3\n");
		correctionMask = correctionMask | 0b00000100;
	};

	printf("correctionMask: "); h.printBits(&h, sizeof(correctionMask), &correctionMask);
	
	unsigned char swapBit;
	swapBit = swapBitTable[correctionMask];
	printf("swapBit: "); h.printBits(&h, sizeof(swapBit), &swapBit);

	unsigned char correctedByte;
	correctedByte = swapBit ^ this->input;
	printf("correctedByte: "); h.printBits(&h, sizeof(correctedByte), &correctedByte);

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