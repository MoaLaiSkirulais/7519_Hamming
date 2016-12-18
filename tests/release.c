{
	/* fake */
	// char *argv[] = {"-d", "arg1", NULL};
	// char *argv[] = {"-e", "../files/sample.txt", NULL};	
	// char *argv[] = {"-d", "../files/sample.txt.encoded", NULL};	
	// int argc = sizeof(argv) / sizeof(char*) - 1;
	
	char *help = "\n"
	"\tuse \n"
	"\t-------\n"
		
	"\t$ tdc_Hamming.exe <-e | -d | -dn> <filename>\n\n"

	"\texplain:\n"
	"\t\t-e      : encode\n"
	"\t\t-d      : decode with correction\n"
	"\t\t-dn     : decode without correction\n"
	"\t\tfilename: absolute or relative path, must exists. \n"
	"\t\t\tWhen -d, any hamming 7,4 encoded file\n"
	"\t\t\tWhen -e, any file\n\n"

	"\toutput:\n"
	"\t\tWhen -d = (filename).decoded\n"
	"\t\tWhen -e = (filename).encoded\n\n";
	
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