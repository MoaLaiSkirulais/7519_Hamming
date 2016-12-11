#include "tdc_Hamming_Controller.h"

/* 
 * decode
 */
static int decode(tdc_Hamming_Controller *this, char *filename) {
	
	int retval = 0;

	/* leo el archivo fuente */
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);

	strcpy(file.inPath, filename);
	retval = file.read(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}

	/* decodeo archivo fuente */
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	retval = decoder.decodeBuffer(&decoder, file.inBuffer);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* escribo archivo de salida encodeado */
	file.outBuffer = decoder.outBuffer; 
	sprintf(file.outPath, "%s%s", file.inPath, ".decoded");
	printf("file.outPath: %s\n", file.outPath);
	retval = file.write(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* fin */
	file.destroy(&file);
	decoder.destroy(&decoder);
	
	return TDC_HAMMING_OK;
	

}

/* 
 * encode
 */
static int encode(tdc_Hamming_Controller *this, char *filename) {

	int retval = 0;

	/* leo el archivo fuente */
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);

	strcpy(file.inPath, filename);
	retval = file.read(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}

	/* encodeo archivo fuente */
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	retval = encoder.encodeBuffer(&encoder, file.inBuffer);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* escribo archivo de salida encodeado */
	file.outBuffer = encoder.outBuffer; 
	sprintf(file.outPath, "%s%s", file.inPath, ".encoded");
	printf("file.outPath: %s\n", file.outPath);
	retval = file.write(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* fin */
	file.destroy(&file);
	encoder.destroy(&encoder);
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_Controller *this) {

	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Controller_init
 */
int tdc_Hamming_Controller_init(tdc_Hamming_Controller *obj) {

	obj->destroy = destroy;
	obj->decode = decode;
	obj->encode = encode;
}