#include <tap.h>
#include "tdc_Hamming_Decoder.h"
#include "tdc_Hamming_Encoder.h"
#include "tdc_Hamming_File.h"

// http://www.ee.unb.ca/cgi-bin/tervo/hamming.pl?L=7&D=3&X=+Receive+&T=1110100

/* ---------------------------- */

int main() {
	
	/* tdc_Hamming_File read */
	{
		tdc_Hamming_File file;	
		tdc_Hamming_File_init(&file);
		
		strcpy(file.inPath, "../files/holaMundo.txt");
		cmp_ok(file.read(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File read");
		file.destroy(&file);
	}
	/* tdc_Hamming_Encoder encodeByte */
	{
		tdc_Hamming_Encoder encoder;
		tdc_Hamming_Encoder_init(&encoder);

		encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		encoder.input = 0b00001110; //espera 1110100 (7,4) 010111100110 (15,11)
		encoder.encodeByte(&encoder);
		cmp_ok(encoder.output, "==", 0b00001110, "tdc_Hamming_Encoder encodeByte");
	}

	/* tdc_Hamming_Encoder encodeBuffer */
	{
		tdc_Hamming_Encoder encoder; 
		tdc_Hamming_Encoder_init(&encoder);

		encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		encoder.encodeBuffer(&encoder, "Hello");
		cmp_ok(encoder.output, "==", 0b00001110, "tdc_Hamming_Encoder encodeBuffer");
	}

	/* tdc_Hamming_Decoder decodeByte */
	{
		tdc_Hamming_Decoder decoder;	
		tdc_Hamming_Decoder_init(&decoder);
		
		decoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		decoder.input = 0b00001110;
		decoder.decodeByte(&decoder);	
		cmp_ok(decoder.output, "==", 0b00001110, "tdc_Hamming_Decoder decodeByte");
	}
	
	/* tdc_Hamming_Decoder decodeBuffer */
	{
		tdc_Hamming_Decoder decoder; 
		tdc_Hamming_Decoder_init(&decoder);

		decoder.type = TDC_HAMMING_ENCODER_TYPE_74;
		decoder.decodeBuffer(&decoder, "Hello");
		cmp_ok(decoder.output, "==", 0b00001110, "tdc_Hamming_Decoder decodeBuffer");
	}
	
	/* tdc_Hamming_File write */
	{
		tdc_Hamming_File file;	
		tdc_Hamming_File_init(&file);

		// printf("file.inBuffer: %s\n", file.inBuffer);
		file.outBuffer = file.inBuffer; 
		strcpy(file.outPath, "../files/holaMundo.out.txt");

		int retval = file.write(&file);
		cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_File write");
		file.destroy(&file);
		
	}
	
	return 0;

}

