{
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
	
	/* ejemplo con eol en el medio */
	tdc_Hamming_Buffer buffer =	{};
	buffer.bytes =	malloc(4);
	buffer.bytes[0] = 0x43; 
	buffer.bytes[1] = 0x68; 
	buffer.bytes[2] = 0x00; 
	buffer.bytes[3] = 0x33;
	buffer.size = 4;
	
	printf("buffer.bytes: %s\n", buffer.bytes);
	encoder.encodeBuffer(&encoder, &buffer, 4);

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
