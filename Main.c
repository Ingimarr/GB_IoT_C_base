/*
 * Main.c
 * Coursework
 * Temperature stats
 * 
 * Copyright 2022 igorb <igorb@DESKTOP-L46ISQD>
 * 
 * 
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "temp_functions.h"


int main(int argc, char **argv)
{
	int opt;
	char *filename=NULL;
	FILE *f=NULL;
	int month=0;
	
	
	while ((opt = getopt(argc, argv, "hf:m:"))!=-1){
		switch(opt){
			case 'h':
				printHelp();
				return 0;
				break;
				
			case 'f':
				printf("This is data source file: ");
				filename=optarg;
				printf("%s\n", filename);
				int len = strlen(filename);
				if((strcmp(filename+len-4,".csv"))!=0){
					printf("Wrong file type. File must have extention .csv\n");
					return 1;
					}
				break;
				
			case 'm':
				month = atoi(optarg);
				
				if ((month<0)||(month>12)){
					printf("Wrong month\nPlease, enter correct month or 0 for statistic of a year\n");
					return 1;
					}
				break;
				
			case '?':
				printf("Wrong argument.\nUse -h key to see the list of avalible arguments\n");
				return 1;
				break;
			default:
				return 1;
			}
		}
	
	if (argc<2) {
		printf("Too few arguments\nUse -h key for help\n");
		return 1;
	} else if (argv[1][1]!='f' && argv[1][1]!='h'){
		printf("wrong argument or order\nUse -h key for help\n");
	} else {	
	
	f=fopen(filename,"r");
	if (f==NULL){
		printf("Can't open file\nPlease, check filename\n");
		return 1;
		}
		
	read_file(f);
	
	calc_data(month);
	
	fclose(f);
	
	return 0;
	}
}

