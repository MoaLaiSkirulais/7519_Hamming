{
	tdc_Hamming_Decoder decoder;	
	tdc_Hamming_Decoder_init(&decoder);

	decoder.input = 0b0101010;
	decoder.decodeByte(&decoder);	
	cmp_ok(decoder.output, "==", 0b0101010, "tdc_Hamming_Decoder decodeByte ok 1");

	decoder.input = 0b1001011;
	decoder.decodeByte(&decoder);	
	cmp_ok(decoder.output, "==", 0b1001011, "tdc_Hamming_Decoder decodeByte ok 2");

	decoder.input = 0b1101011;
	decoder.decodeByte(&decoder);	
	cmp_ok(decoder.output, "==", 0b1001011, "tdc_Hamming_Decoder decodeByte wrong 1");

	decoder.input = 0b0011101;
	decoder.decodeByte(&decoder);	
	cmp_ok(decoder.output, "==", 0b0011001, "tdc_Hamming_Decoder decodeByte wrong 2");

	decoder.destroy(&decoder);
}
