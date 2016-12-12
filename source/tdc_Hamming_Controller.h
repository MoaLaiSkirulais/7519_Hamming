#ifndef tdc_Hamming_Controller_H
#define tdc_Hamming_Controller_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Decoder.h"
#include "tdc_Hamming_Encoder.h"
#include "tdc_Hamming_File.h"

/* 
 * tdc_Hamming_Controller
 */
typedef struct tdc_Hamming_Controller {
	
	tdc_Hamming_Decoder decoder;
	tdc_Hamming_Encoder encoder; 
		
	int (*destroy)();
	int (*decode)();
	int (*encode)();

} tdc_Hamming_Controller;

/* 
 * tdc_Hamming_Controller_init 
 */
int tdc_Hamming_Controller_init(tdc_Hamming_Controller *obj);

#endif
