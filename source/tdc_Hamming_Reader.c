#include "tdc_Hamming_Reader.h"

/* 
 * tdc_Hamming_Reader_read
 */
static int read(tdc_Hamming_Reader *this) {

	return TDC_HAMMING_READER_OK;

}

/*
 * tdc_Hamming_Reader_init
 */
int tdc_Hamming_Reader_init(tdc_Hamming_Reader *obj) {

	obj->read = read;
}