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

	/* lectura */
	if (file) {

		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);  
		
		this->inBuffer.bytes = malloc(fsize + 1);		
		this->inBuffer.size = fsize;
		
		fread(this->inBuffer.bytes, fsize, 1, file);
		this->inBuffer.bytes[fsize] = '\0';
		this->size = fsize;
		
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

	/* Write your buffer to disk */
	fwrite(this->outBuffer.bytes, this->outBuffer.size, 1, file);
	fclose(file);
	this->size = this->outBuffer.size;

	/* fin */
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_File *this) {
	
	if (this->inBuffer.bytes){
		free(this->inBuffer.bytes);
		this->inBuffer.bytes = NULL;
	}

	if (this->outBuffer.bytes){
		free(this->outBuffer.bytes);
		this->outBuffer.bytes = NULL;
	}

	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_File_init()
 */
int tdc_Hamming_File_init(tdc_Hamming_File *obj) {
	
	obj->inBuffer.bytes = NULL;	
	obj->outBuffer.bytes = NULL;

	obj->destroy = destroy;
	obj->read = read;
	obj->write = write;
}