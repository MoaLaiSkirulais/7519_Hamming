{
	/* decode */
	tdc_Hamming_Controller controller; 
	tdc_Hamming_Controller_init(&controller);

	// controller.decoder.mode = TDC_HAMMING_DECODER_MODE_NOCORRECT;
	int retval = controller.decode(&controller, "../files/sampleErrors.encoded");
	cmp_ok(retval, "==", TDC_HAMMING_OK, "tdc_Hamming_Controller decode");
	controller.destroy(&controller);
}

