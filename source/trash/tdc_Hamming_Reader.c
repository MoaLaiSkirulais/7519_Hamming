#include "tdc_Hamming_Reader.h"

static void printBits(size_t const size, void const * const ptr);

/* 
 * tdc_Hamming_Reader_read
 */
static int read(tdc_Hamming_Reader *this) {

	/* open file */
	int c;
	FILE *file;
	file = fopen(sourcePath, "r");
	
	/* error de apertura */
	if (!file) {
		return TDC_HAMMING_READER_ERROR_INVALID_SOURCE_FILE;
	}
	
	char buffer; 
	int byteCount; 
	
	/* lectura ok lee byte a byte */
	if (file) {
		
	    fread(readedBuffer, yorBufferSize, 1, pFile);

		
		// byteCount = fread(&buffer, 1, 1, file);
		// while (byteCount > 0){
			// printf("buffer: %c\n", buffer);
			// // printf("byteCount: %d\n", byteCount);
			// byteCount = fread(&buffer, 1, 1, file);
			// printBits(sizeof(buffer), &buffer);
		// }		
	}

	/* fin */
	printf("\n");
	return TDC_HAMMING_READER_OK;

}

/*
 * printBits - 
 * assumes little endian
 */
static void printBits(size_t const size, void const *const ptr) {

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
 * tdc_Hamming_Reader_init
 */
int tdc_Hamming_Reader_init(tdc_Hamming_Reader *obj) {

	obj->read = read;
}