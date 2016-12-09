#include "tdc_Hamming_Writer.h"

/* 
 * tdc_Hamming_Writer_write
 */
static int write(tdc_Hamming_Writer *this) {

	char sourcePath[100];
	strcpy(sourcePath, "../files/holaMundo.out.txt");
	
	/* open file */
	int c;
	FILE *file;
	file = fopen(sourcePath, "wb");
	// FILE *fp = fopen("scores.dat", "ab+");

	
	/* error de apertura */
	if (!file) {
		return TDC_HAMMING_WRITER_ERROR_INVALID_TARGET_FILE;
	}
	
	this->buffer = malloc(strlen("HelloWorld!"));
	sprintf(this->buffer, "%s", "HelloWorld!");

	/* Write your buffer to disk. */
	fwrite(this->buffer, strlen(this->buffer) + 1, 1, file);

	fclose(file);
	free(this->buffer);

	/* fin */
	printf("\n");
	return TDC_HAMMING_READER_OK;

}

/*
 * tdc_Hamming_Writer_init
 */
int tdc_Hamming_Writer_init(tdc_Hamming_Writer *obj) {

	obj->write = write;
}