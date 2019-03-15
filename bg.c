/* Akhileswar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define path "/proc/"
#define SIZE 1

int main(){
	
	FILE *file = NULL;
	char path_buffer[15];
	int pid = 0;
	char line[50];
	char *field = (char *) malloc(SIZE);
	char *value;
	
	//file = fopen(fopen(path,"r");
	//printf(path);
	while(pid < 10){
		sprintf(path_buffer,"/proc/%d/status",pid);
		//printf("\npath %d: %s",pid,buffer);
		file = fopen(path_buffer,"r");
		if(file != NULL){
			  //file or pid doesn't exist
		
			while(fgets(line,50,file)){
				printf("\n%s",line);
				
				//To get the field as a seperate string
				for(int i = 0; line[i] != ' '; i++){
					field  = (char *) realloc(field,SIZE + i);
					*(field + i) = line[i];
				}		
			}
		}
