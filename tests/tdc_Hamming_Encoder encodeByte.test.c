{
	tdc_Hamming_Encoder encoder;
	tdc_Hamming_Encoder_init(&encoder);

	encoder.type = TDC_HAMMING_ENCODER_TYPE_74;
	encoder.input = 0b00000100; 
	encoder.encodeByte(&encoder);
	cmp_ok(encoder.output, "==", 0b0101010, "tdc_Hamming_Encoder encodeByte 1");

	encoder.input = 0b00000011; 
	encoder.encodeByte(&encoder);
	cmp_ok(encoder.output, "==", 0b0011110, "tdc_Hamming_Encoder encodeByte 2");

	encoder.input = 0b0110; 
	encoder.encodeByte(&encoder);
	cmp_ok(encoder.output, "==", 0b0110011, "tdc_Hamming_Encoder encodeByte 3");
	encoder.destroy(&encoder);
}

