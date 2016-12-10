#include <tap.h>
#include "tdc_Hamming_Decoder.h"
#include "tdc_Hamming_Encoder.h"
#include "tdc_Hamming_File.h"

// http://www.ee.unb.ca/cgi-bin/tervo/hamming.pl?L=7&D=3&X=+Receive+&T=1110100

/* ---------------------------- */

int main() {

	/* globals */	
	char *buffer;

	/* tdc_Hamming_File read */
	{
		tdc_Hamming_File file;	
		tdc_Hamming_File_init(&file);
		
		strcpy(file.inPath, "../files/holaMundo.txt");
		cmp_ok(file.read(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File read");
		
		buffer = malloc(strlen(file.inBuffer) + 1); 
		// buffer = malloc(sizeof(file.inBuffer)); /* strlen no incluye el \0, sizeof sí */
		strcpy(buffer, file.inBuffer);
		// printf("buffer: %s\n", buffer);
		file.destroy(&file);
	}

	/* tdc_Hamming_Encoder encodeByte */
	{
		tdc_Hamming_Encoder encoder;
		tdc_Hamming_Encoder_init(&encoder);

		encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		encoder.input = 0b00000100; 
		encoder.encodeByte(&encoder);
		cmp_ok(encoder.output, "==", 0b0101010, "tdc_Hamming_Encoder encodeByte 1");

		encoder.input = 0b00000011; 
		encoder.encodeByte(&encoder);
		cmp_ok(encoder.output, "==", 0b0111100, "tdc_Hamming_Encoder encodeByte 2");

		encoder.input = 0b0110; 
		encoder.encodeByte(&encoder);
		cmp_ok(encoder.output, "==", 0b1100110, "tdc_Hamming_Encoder encodeByte 3");
		encoder.destroy(&encoder);
	}

	/* tdc_Hamming_Encoder encodeBuffer */
	{
		tdc_Hamming_Encoder encoder; 
		tdc_Hamming_Encoder_init(&encoder);

		encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		printf(">>> buffer: %s\n", buffer);
		encoder.encodeBuffer(&encoder, buffer);

		char expected[10]="";
		sprintf(expected, "%s%c", expected, 0b00101010); 
		sprintf(expected, "%s%c", expected, 0b00111100); 
		sprintf(expected, "%s%c", expected, 0b01100110); 
		sprintf(expected, "%s%c", expected, 0b01101001); 
		sprintf(expected, "%s%c", expected, 0b00111100); 
		sprintf(expected, "%s%c", expected, 0b00111100);

		cmp_mem(encoder.outBuffer, expected, 6, "tdc_Hamming_Encoder encodeBuffer");
		// buffer = encoder.outBuffer; 
		buffer = realloc(buffer, strlen(encoder.outBuffer) + 1); 
		strcpy(buffer, encoder.outBuffer);
		encoder.destroy(&encoder);

	}

	// /* tdc_Hamming_Decoder decodeByte */
	// {
		// tdc_Hamming_Decoder decoder;	
		// tdc_Hamming_Decoder_init(&decoder);
		
		// decoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		// decoder.input = 0b00001110;
		// decoder.decodeByte(&decoder);	
		// // cmp_ok(decoder.output, "==", 0b00001110, "tdc_Hamming_Decoder decodeByte");
	// }
	
	// /* tdc_Hamming_Decoder decodeBuffer */
	// {
		// tdc_Hamming_Decoder decoder; 
		// tdc_Hamming_Decoder_init(&decoder);

		// decoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		// decoder.decodeBuffer(&decoder, "Hello");
		// // cmp_ok(decoder.output, "==", 0b00001110, "tdc_Hamming_Decoder decodeBuffer");
	// }

	/* tdc_Hamming_File write */
	{
		tdc_Hamming_File file;	
		tdc_Hamming_File_init(&file);

		file.outBuffer = buffer; 
		strcpy(file.outPath, "../files/holaMundo.out.txt");

		int retval = file.write(&file);
		cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_File write");
		file.destroy(&file);
		
	}
	
	free(buffer);	
	return 0;

}

