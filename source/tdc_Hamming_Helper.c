#include "tdc_Hamming_Helper.h"

/*
 * printBits - 
 * assumes little endian
 */
static int printBits(tdc_Hamming_Helper *this, size_t const size, void const *const ptr) {

	// printf("size: %zu\n", size);
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1; i>=0; i--)
    {
        for (j=7; j>=0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

/*
 * tdc_Hamming_Helper_init
 */
int tdc_Hamming_Helper_init(tdc_Hamming_Helper *obj) {

	obj->printBits = printBits;
}