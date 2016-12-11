{
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
	// printf(">>> buffer: %s\n", buffer);
	encoder.encodeBuffer(&encoder, buffer);

	char expected[10]="";
	sprintf(expected, "%s%c", expected, 0b0101010); 
	sprintf(expected, "%s%c", expected, 0b0011110); 
	sprintf(expected, "%s%c", expected, 0b0110011); 
	sprintf(expected, "%s%c", expected, 0b1001011); 
	sprintf(expected, "%s%c", expected, 0b0011110); 
	sprintf(expected, "%s%c", expected, 0b0011110);

	cmp_mem(encoder.outBuffer, expected, 6, "tdc_Hamming_Encoder encodeBuffer");
	// buffer = encoder.outBuffer; 
	buffer = realloc(buffer, strlen(encoder.outBuffer) + 1); 
	strcpy(buffer, encoder.outBuffer);
	encoder.destroy(&encoder);

}
