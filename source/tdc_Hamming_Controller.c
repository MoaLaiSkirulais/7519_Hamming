#include "tdc_Hamming_Controller.h"

/* 
 * decode
 */
static int decode(tdc_Hamming_Controller *this, char *filename) {
	
	/* start timer */
	tdc_Hamming_Time t;
	tdc_Hamming_Time_init(&t);
	t.start(&t);	
	
	/* leo el archivo fuente */
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);

	int retval = 0;
	strcpy(file.inPath, filename);
	retval = file.read(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}

	/* decodeo archivo fuente */
	retval = this->decoder.decodeBuffer(&this->decoder, &file.inBuffer);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}

	/* traspaso buffer de salida encodeado */
	file.outBuffer.bytes = malloc(this->decoder.outBuffer.size); 
	memcpy(file.outBuffer.bytes, this->decoder.outBuffer.bytes, this->decoder.outBuffer.size); 
	file.outBuffer.size = this->decoder.outBuffer.size; 

	/* escribo a disco*/
	sprintf(file.outPath, "%s%s", file.inPath, ".decoded");
	retval = file.write(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* end timer */
	t.end(&t);
	
	/* imprimo reporte */
	printf("\n");
	printf("\t summary\n");
	printf("\t -------\n");
	printf("\t errors : %d bits\n", this->decoder.stats.totalErrors);
	printf("\t file   : %s\n", file.outPath);
	printf("\t size   : %d bytes\n", file.size);
	printf("\t elapsed: %d seconds\n", t.elapsed(&t));
	printf("\n");
	
	/* fin */
	file.destroy(&file);
	return TDC_HAMMING_OK;	

}

/* 
 * encode
 */
static int encode(tdc_Hamming_Controller *this, char *filename) {
	
	/* start timer */
	tdc_Hamming_Time t;
	tdc_Hamming_Time_init(&t);
	t.start(&t);	

	/* leo el archivo fuente */
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);

	int retval = 0;
	strcpy(file.inPath, filename);
	retval = file.read(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}

	/* encodeo archivo fuente */
	retval = this->encoder.encodeBuffer(&this->encoder, &file.inBuffer);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* escribo archivo de salida encodeado */
	file.outBuffer.bytes = malloc(this->encoder.outBuffer.size);	
	memcpy(file.outBuffer.bytes, this->encoder.outBuffer.bytes, this->encoder.outBuffer.size); 
	file.outBuffer.size = this->encoder.outBuffer.size; 

	/* escribo a disco*/
	sprintf(file.outPath, "%s%s", file.inPath, ".encoded");
	retval = file.write(&file);
	if (retval != TDC_HAMMING_OK){
		return retval;
	}
	
	/* end timer */
	t.end(&t);
	
	/* imprimo reporte */
	printf("\n");
	printf("\t summary\n");
	printf("\t -------\n");
	printf("\t file   : %s\n", file.outPath);
	printf("\t size   : %d bytes\n", file.size);
	printf("\t elapsed: %d seconds\n", t.elapsed(&t));
	printf("\n");
	
	/* fin */
	file.destroy(&file);
	return TDC_HAMMING_OK;

}

/* 
 * destroy()
 */
static int destroy(tdc_Hamming_Controller *this) {

	this->decoder.destroy(&this->decoder); 
	this->encoder.destroy(&this->encoder);
	return TDC_HAMMING_OK;

}

/*
 * tdc_Hamming_Controller_init
 */
int tdc_Hamming_Controller_init(tdc_Hamming_Controller *obj) {
	
	tdc_Hamming_Decoder_init(&obj->decoder);
	tdc_Hamming_Encoder_init(&obj->encoder);

	obj->destroy = destroy;
	obj->decode = decode;
	obj->encode = encode;
}