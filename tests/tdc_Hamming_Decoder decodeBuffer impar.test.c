{
	
	/* comienza un decode impar */
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	char buffer[10]="";
	sprintf(buffer, "%s%c", buffer, 0b0101010); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 
	sprintf(buffer, "%s%c", buffer, 0b0110011); 
	sprintf(buffer, "%s%c", buffer, 0b1001011); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 

	decoder.decodeBuffer(&decoder, buffer);
	cmp_mem(decoder.outBuffer, "Ch3", 3, "tdc_Hamming_Decoder decodeBuffer impar.test.c");
	printf("decoder.outBuffer: %s\n", decoder.outBuffer);
	decoder.destroy(&decoder);
}

