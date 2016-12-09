#include "tdc_Hamming_File.h"

/* 
 * tdc_Hamming_File.read()
 */
static int read(tdc_Hamming_File *this) {

	/* open file */
	int c;
	FILE *file;
	file = fopen(this->inPath, "r");
	
	/* error de apertura */
	if (!file) {
		return TDC_HAMMING_FILE_ERROR_INVALID_SOURCE_FILE;
	}

	char buffer; 
	int byteCount; 

	/* lectura ok lee byte a byte */
	if (file) {
		
	    // fread(readedBuffer, yorBufferSize, 1, pFile);
		
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);  //same as rewind(f);

		this->inBuffer = realloc(this->inBuffer, fsize + 1);
		fread(this->inBuffer, fsize, 1, file);
		// printf("this->inBuffer: %s\n", this->inBuffer);
		
		// byteCount = fread(&buffer, 1, 1, file);
		// while (byteCount > 0){
			// printf("buffer: %c\n", buffer);
			// // printf("byteCount: %d\n", byteCount);
			// byteCount = fread(&buffer, 1, 1, file);
			// printBits(sizeof(buffer), &buffer);
		// }		
	}

	/* fin */
	fclose(file);
	return TDC_HAMMING_OK;

}

/* 
 * tdc_Hamming_File.write()
 */
static int write(tdc_Hamming_File *this) {

	/* open file */
	FILE *file;
	file = fopen(this->outPath, "wb");
	
	/* error de apertura */
	if (!file) {
		return TDC_HAMMING_FILE_ERROR_INVALID_TARGET_FILE;
	}
	
	// this->outBuffer = malloc(strlen("HelloWorld!"));
	// sprintf(this->buffer, "%s", "HelloWorld!");

	/* Write your buffer to disk. */
	fwrite(this->outBuffer, strlen(this->outBuffer) + 1, 1, file);

	fclose(file);
	// free(this->outBuffer);

	/* fin */
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_File *this) {

	free(this->inBuffer);
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_File_init
 */
int tdc_Hamming_File_init(tdc_Hamming_File *obj) {
	
	obj->inBuffer = malloc(sizeof(char));
	strcpy(obj->inBuffer, "");

	obj->destroy = destroy;
	obj->read = read;
	obj->write = write;
}