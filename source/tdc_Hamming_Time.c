#include "tdc_Hamming_Time.h"

/* ------------------ */ 

static int start(tdc_Hamming_Time *this) {
	time(&this->_start_t);
	return 1;
}

/* ------------------ */ 

static int end(tdc_Hamming_Time *this) {
	time(&this->_end_t);
	return 1;
}

/* ------------------ */ 

static int elapsed(tdc_Hamming_Time *this) {
	
	double diff_t;	
	diff_t = difftime(this->_end_t, this->_start_t);
	return 1;
}

/* ------------------ */

int tdc_Hamming_Time_init(tdc_Hamming_Time *obj){
	
	obj->start = start;
	obj->end = end;
	obj->elapsed = elapsed;

	return 0;
}