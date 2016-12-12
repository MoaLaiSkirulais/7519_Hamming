{
	
	/* 
	 * encodeo archivo fuente 
	 */
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	encoder.encodeBuffer(&encoder, "Javié");

	/* 
	 * decode 
	 */
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	decoder.decodeBuffer(&decoder, encoder.outBuffer);
	
	printf("\n");	
	printf("encoder.outBuffer: %s\n", encoder.outBuffer);	
	printf("decoder.outBuffer: %s\n", decoder.outBuffer);
	
	/* fin */
	encoder.destroy(&encoder);
	decoder.destroy(&decoder);
	// free(myBuffer);	
}

