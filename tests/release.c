{
	/* fake */
	// char *argv[] = {"-d", "arg1", NULL};
	// char *argv[] = {"-e", "../files/sample.txt", NULL};	
	// char *argv[] = {"-d", "../files/sample.txt.encoded", NULL};	
	// int argc = sizeof(argv) / sizeof(char*) - 1;
	
	char *help = "uso:\n\
	-d | -e | -dn (decode|encode|decode but no correct)\n\
	filename (existing file, to encode or decode)";
	
	// printf("argc: %d\n", argc);
	// printf("argv[0]: %s\n", argv[0]);

	/* start */
	if (argc!=3) {
		printf("error: argumentos invalidos\n");
		printf("%s\n", help);
		return -1;
	}

	/* operation */
	char operation[10] = "none";
	if (strcmp(argv[1], "-e") == 0) {strcpy(operation, "encode");}
	if (strcmp(argv[1], "-d") == 0) {strcpy(operation, "decode");}
	if (strcmp(argv[1], "-dn") == 0) {strcpy(operation, "decode_nocorrect");}

	if (strcmp(operation, "none") == 0) {
		printf("Operacion invalida\n");
		return -1;
	}

	/* encode */
	if (strcmp(operation, "encode") == 0) {			
		
		tdc_Hamming_Controller controller; 
		tdc_Hamming_Controller_init(&controller);

		int retval = controller.encode(&controller, argv[2]);
		cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller encode");
		controller.destroy(&controller);

	}

	/* decode */
	if (strcmp(operation, "decode") == 0) {			

		tdc_Hamming_Controller controller; 
		tdc_Hamming_Controller_init(&controller);

		int retval = controller.decode(&controller, argv[2]);
		cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller decode");
		controller.destroy(&controller);

	}
	
	/* decode no correct */
	if (strcmp(operation, "decode_nocorrect") == 0) {			

		tdc_Hamming_Controller controller; 
		tdc_Hamming_Controller_init(&controller);
		
		controller.decoder.mode = TDC_HAMMING_DECODER_MODE_NOCORRECT;
		int retval = controller.decode(&controller, argv[2]);
		cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller decode");
		controller.destroy(&controller);

	}
}