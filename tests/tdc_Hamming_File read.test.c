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

