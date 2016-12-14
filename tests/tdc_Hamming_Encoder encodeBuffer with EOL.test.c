{
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
	// char *buffer = "Ch3";
	// char *buffer = "x43x68x33";
	// char *buffer = "x43x68x01x33";
	// unsigned char buffer[4] = {0x43, 0x68, 0x01, 0x33};
	unsigned char buffer[4] = {0x43, 0x68, 0x00, 0x33};
	printf(">>> buffer: %s\n", buffer);
	encoder.encodeBuffer(&encoder, buffer, 4);

	char expected[10]="";
	sprintf(expected, "%s%c", expected, 0b10101010); 
	sprintf(expected, "%s%c", expected, 0b10011110); 
	
	sprintf(expected, "%s%c", expected, 0b10110011); 
	sprintf(expected, "%s%c", expected, 0b11001011); 
	
	sprintf(expected, "%s%c", expected, 0b10000000); 
	sprintf(expected, "%s%c", expected, 0b10000000);

	sprintf(expected, "%s%c", expected, 0b10011110); 
	sprintf(expected, "%s%c", expected, 0b10011110);

	cmp_mem(encoder.outBuffer, expected, 6, "tdc_Hamming_Encoder encodeBuffer");
	encoder.destroy(&encoder);

}
