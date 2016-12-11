{
	tdc_Hamming_File file;	
	tdc_Hamming_File_init(&file);

	file.outBuffer = buffer; 
	strcpy(file.outPath, "../files/holaMundo.out.txt");

	int retval = file.write(&file);
	cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_File write");
	file.destroy(&file);
	
}
