#include <stdio.h>
#include "temp_functions.h"

static temp_data_t temp_data[13]={{0,0,0,0}};
static char * month_name[12] = {"January", "February","March","April","May","June","July", "August","September", "October", "November", "December"};

void read_file(FILE *f){
	
	int year, month, day, hour, minute, temperature;
	int line=1;
	char buffer[30];
	const int success_fields=6;
	int prev_month=-1;
	int ch;
	int error_flag=0;
	int fields=0;
	
	
	for (line=1;fscanf(f,"%[^\n]s",buffer)!=-1;line++){
		
		do{ch=fgetc(f);} while(ch!='\n'&&ch!=EOF);
		//while (fgetc(f)!='\n');
		
		fields=sscanf(buffer, "%d;%d;%d;%d;%d;%d",&year, &month, &day, &hour, &minute,&temperature);
		if (fields!=success_fields){
			printf("Error at line %d. Wrong line format\n",line);
			continue;
			}

		if (year<2000 || year>2100){
			error_flag=1;
			printf("Error at line %d. Incorrect year\n",line);
			}
			
		if (month<1 || month>12){
			error_flag=1;
			printf("Error at line %d. Incorrect month\n",line);
			}
			
		if (day<1 || day>31){
			error_flag=1;
			printf("Error at line %d. Incorrect day\n",line);
			}
			
		if (hour<0 || hour>23){
			error_flag=1;
			printf("Error at line %d. Incorrect hour\n",line);
			}
			
		if (minute<0 || minute>59){
			error_flag=1;
			printf("Error at line %d. Incorrect minute\n",line);
			}
			
		if (temperature<-99 || temperature>99){
			error_flag=1;
			printf("Error at line %d. Incorrect temperature\n",line);
			}
			
		if(error_flag==0)
			{
		//		printf("line %d is ok\n", line);
				
				temp_data[month].sum+=temperature;
				temp_data[month].n++;
				
				if (month!=prev_month){
					temp_data[month].t_max=temperature;
					temp_data[month].t_min=temperature;
					}
				prev_month=month;
				
				if (temperature>temp_data[month].t_max){
					temp_data[month].t_max=temperature;
					}
					
				if (temperature<temp_data[month].t_min){
					temp_data[month].t_min=temperature;
					} 
			}else{
				error_flag=0;
				}
		
		}
		
	printf("Reading the file is over\n");
	}

	

void calc_data(int month){
	if(month!=0){
		if (temp_data[month].n==0) {
			printf("No data for %s\n", month_name[month-1]);
		}else{
			printf("This is data for %s:\n",month_name[month-1]);
			printf("Avg.t=%d\xF8\x43\nMax.t=%d\xF8\x43\nMin.t=%d\xF8\x43\n",temp_data[month].sum/temp_data[month].n, temp_data[month].t_max,temp_data[month].t_min);
			}
		}else{
			
			temp_data[month].t_max=-99;
			temp_data[month].t_min=99;
			
			for(int i=1;i<13;i++){
				temp_data[month].sum+=temp_data[i].sum;
				temp_data[month].n+=temp_data[i].n;
				
				if(temp_data[i].n>0){
					if (temp_data[i].t_max>temp_data[month].t_max){
						temp_data[month].t_max=temp_data[i].t_max;
						}
						
					if (temp_data[i].t_min<temp_data[month].t_min){
						temp_data[month].t_min=temp_data[i].t_min;
						} 
					}
				}
			
			if (temp_data[0].n==0){
				printf("No data for a year\n");
				}else{
					printf("This is data for a year:\n");
					printf("Avg.t=%d\xF8\x43\nMax.t=%d\xF8\x43\nMin.t=%d\xF8\x43\n",temp_data[month].sum/temp_data[month].n, temp_data[month].t_max,temp_data[month].t_min);
					}
		}
	}


void printHelp(){
	printf("================Tempstat:Read and analyse temperature sensors data=======================\n");
	printf("This program processes data from the temperature sensor\n");
	printf("Data must be in a .csv file and has a structure:\n");
	printf("YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE\n");
	printf("dddd;mm;dd;hh;mm;temperature\n\n");
	printf("Run the program using -f <filename.csv> key\n");
	printf("Example: tempstat.exe -f temperature_big.csv\n\n");
	printf("Options:\n-m[0-12]: get statistic for a month(where 1 is January) or for a year (if -m0)\n");
	printf("-h help\n");
	printf("=========================================================================================\n");
	
	}
