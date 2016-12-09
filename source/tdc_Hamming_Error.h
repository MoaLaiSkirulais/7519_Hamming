#ifndef tdc_Hamming_Error_H
#define tdc_Hamming_Error_H

typedef enum {

	/* 00 */ TDC_HAMMING_OK,
	/* 01 */ TDC_HAMMING_FILE_ERROR_INVALID_SOURCE_FILE, 
	/* 02 */ TDC_HAMMING_FILE_ERROR_INVALID_TARGET_FILE
	
} tdc_Hamming_Error;

#endif