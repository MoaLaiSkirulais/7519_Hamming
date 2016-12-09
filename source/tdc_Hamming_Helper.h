#ifndef tdc_Hamming_Helper_H
#define tdc_Hamming_Helper_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tdc_Hamming_Error.h"

/* 
 * tdc_Hamming_Helper
 */
typedef struct tdc_Hamming_Helper {

	int (*printBits)();

} tdc_Hamming_Helper;

/* 
 * tdc_Hamming_Helper_init 
 */
int tdc_Hamming_Helper_init(tdc_Hamming_Helper *obj);

#endif
