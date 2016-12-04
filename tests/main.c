#include <tap.h>
#include "tdc_Hamming_Reader.h"

/* ---------------------------- */

int main() {
	
	/* tdc_Hamming_Reader read */
	tdc_Hamming_Reader hr;	
	tdc_Hamming_Reader_init(&hr);

	cmp_ok(hr.read(&hr), "==", TDC_HAMMING_READER_OK, "tdc_Hamming_Reader read");
	
	return 0;

}

