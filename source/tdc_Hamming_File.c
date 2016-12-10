#include "tdc_Hamming_File.h"

/* 
 * read()
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

		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);  //same as rewind(f);
		
		// printf("fsize: %lu\n", fsize);

		this->inBuffer = realloc(this->inBuffer, fsize + 1);		
		// printf("this->inBuffer: %ld\n", sizeof(this->inBuffer));
		
		// char *aux = malloc(111);	
		// printf("aux: %lu\n", sizeof(aux));
		// strcpy(aux, "hol");
		// printf("aux: %ld\n", sizeof(aux));

		fread(this->inBuffer, fsize, 1, file);
		this->inBuffer[fsize] = '\0';
		// printf("this->inBuffer: %s\n", this->inBuffer);
		
	}

	/* fin */
	fclose(file);
	return TDC_HAMMING_OK;

}

/* 
 * write()
 */
static int write(tdc_Hamming_File *this) {

	/* open file */
	FILE *file;
	file = fopen(this->outPath, "wb");

	/* error de apertura */
	if (!file) {
		return TDC_HAMMING_FILE_ERROR_INVALID_TARGET_FILE;
	}

	/* Write your buffer to disk. */
	fwrite(this->outBuffer, strlen(this->outBuffer) + 1, 1, file);
	fclose(file);

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
 * tdc_Hamming_File_init()
 */
int tdc_Hamming_File_init(tdc_Hamming_File *obj) {
	
	obj->inBuffer = malloc(sizeof(char));
	strcpy(obj->inBuffer, "");	

	obj->destroy = destroy;
	obj->read = read;
	obj->write = write;
}