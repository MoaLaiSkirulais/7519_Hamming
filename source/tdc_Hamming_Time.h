#ifndef tdc_Hamming_Time_H
#define tdc_Hamming_Time_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ------------------ */ 

typedef struct tdc_Hamming_Time {
	
	time_t _start_t;
	time_t _end_t;

	int (*start)();
	int (*end)();	
	int (*elapsed)();	
	
} tdc_Hamming_Time;

/* ------------------ */ 

int tdc_Hamming_Time_init();

#endif