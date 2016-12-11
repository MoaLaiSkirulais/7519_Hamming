{
	
	/* 
	 * leo el archivo fuente 
	 */
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);
	
	strcpy(file.inPath, "../files/holaMundo.txt");
	cmp_ok(file.read(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File read");

	/* 
	 * encodeo archivo fuente 
	 */
	tdc_Hamming_Encoder encoder; 
	tdc_Hamming_Encoder_init(&encoder);

	encoder.encodeBuffer(&encoder, file.inBuffer);

	char expected[10]="";
	sprintf(expected, "%s%c", expected, 0b0101010); 
	sprintf(expected, "%s%c", expected, 0b0011110); 
	sprintf(expected, "%s%c", expected, 0b0110011); 
	sprintf(expected, "%s%c", expected, 0b1001011); 
	sprintf(expected, "%s%c", expected, 0b0011110); 
	sprintf(expected, "%s%c", expected, 0b0011110);

	cmp_mem(encoder.outBuffer, expected, 6, "tdc_Hamming_Encoder encodeBuffer");
	
	/* 
	 * escribo archivo de salida encodeado 
	 */
	file.outBuffer = encoder.outBuffer; 
	printf("strlen(encoder.outBuffer): %lu\n", strlen(encoder.outBuffer));
	strcpy(file.outPath, "../files/holaMundo.out.txt");

	cmp_ok(file.write(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File write");
	
	/* 
	 * read buffer usando la salida del encoder 
	 */
	strcpy(file.inPath, "../files/holaMundo.out.txt");
	cmp_ok(file.read(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File read");
	
	/* 
	 * decode 
	 */
	tdc_Hamming_Decoder decoder; 
	tdc_Hamming_Decoder_init(&decoder);

	decoder.decodeBuffer(&decoder, file.inBuffer);
	cmp_mem(decoder.outBuffer, "Ch3", 3, "tdc_Hamming_Decoder decodeFile");
	
	/* 
	 * escribo re-encodeado a un gemelo del source y termino
	 */
	file.outBuffer = decoder.outBuffer; 
	strcpy(file.outPath, "../files/holaMundo.mirror.txt");

	cmp_ok(file.write(&file), "==", TDC_HAMMING_OK, "tdc_Hamming_File write");
	
	/* fin */
	file.destroy(&file);
	encoder.destroy(&encoder);
	decoder.destroy(&decoder);
	// free(myBuffer);	
}

