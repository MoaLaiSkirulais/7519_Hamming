{
	/* encode */
	tdc_Hamming_Controller controller; 
	tdc_Hamming_Controller_init(&controller);

	int retval = controller.encode(&controller, "../files/sample.jpg");
	cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller encode");
	controller.destroy(&controller);
}

{
	/* decode */
	tdc_Hamming_Controller controller; 
	tdc_Hamming_Controller_init(&controller);

	int retval = controller.decode(&controller, "../files/sample.jpg.encoded");
	cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller decode");
	controller.destroy(&controller);
}

