#ifndef TEMP_FUNCTIONS_H
#define TEMP_FUNCTIONS_H

typedef struct
{
	int sum;
	int n;
	int t_max;
	int t_min;
	}temp_data_t;

#include <stdio.h>


void read_file(FILE *);
void calc_data(int);
void printHelp(void);
	
#endif
