{
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	char buffer[10]="";
	sprintf(buffer, "%s%c", buffer, 0b0101010); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 
	sprintf(buffer, "%s%c", buffer, 0b0110011); 
	sprintf(buffer, "%s%c", buffer, 0b1001011); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); 
	sprintf(buffer, "%s%c", buffer, 0b0011110); // dps conviene tomarlo del file

	decoder.decodeBuffer(&decoder, buffer);
	cmp_mem(decoder.outBuffer, "Ch3", 3, "tdc_Hamming_Decoder decodeBuffer");
	decoder.destroy(&decoder);
}

