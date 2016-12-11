{
	
	/* comienza un decode impar */
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	char buffer[10]="";

	decoder.decodeBuffer(&decoder, buffer);
	cmp_mem(decoder.outBuffer, "", 3, "tdc_Hamming_Decoder decodeBuffer zeroBytes.c");
	printf("decoder.outBuffer: %s\n", decoder.outBuffer);
	decoder.destroy(&decoder);
}

