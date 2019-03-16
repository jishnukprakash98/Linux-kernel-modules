/* Akhileswar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE 1

int main(){
	
	FILE *file = NULL;
	char path_buffer[15];
	int pid = 1;
	char line[10];
	//char *name = (char *) malloc(SIZE);
	char state;

	
	while(pid < 10){
		sprintf(path_buffer,"/proc/%d/stat",pid);
		
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
		
			while(fscanf(file,"%s",line)){
				
				//to get the process name
				if(line[0] == '('){

				}

				//to get the process state
				if(line[0] == 'S' || line[0] == 'R' || line[0] == 'T' || line[0] == 'I'){
					state = line[0];
					break;
				}
				
				//To get the field as a seperate string
				/*
				for(int i = 0; line[i] != '\t'; i++){
					field  = (char *) realloc(field,SIZE + i);
					*(field + i) = line[i];
				}
				*/		
			}
			printf("pid:%d state:%c\n",pid,state);
		}
		pid++;
	}
}

