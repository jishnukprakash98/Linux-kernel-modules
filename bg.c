/* Akhileswar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define SIZE 1

int main(){
	
	FILE *file = NULL;
	char path_buffer[15];
	int pid = 2000;
	char line[10];
	
	//char *name = (char *) malloc(SIZE);
	char state;
	int count = 0;
	int pgrp = 0;
	int tpgid = 0;
	int session_id = 0;
	//int call_pid = getpid();
	//int call_sid = getsid(call_pid);

	
	while(pid < 2100){
		sprintf(path_buffer,"/proc/%d/stat",pid);
		
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
			count = 0;
			while(fscanf(file,"%s",line)){
				
				count++;

				//to get the process name
				if(line[0] == '('){

				}
				if(count == 5){
					pgrp = atoi(line);
				}
				if(count == 6){
					session_id = atoi(line);
				}
				if(count == 8){
					tpgid = atoi(line);
					break;
				}

				//to get the process state
				if(line[0] == 'S' || line[0] == 'R' || line[0] == 'T' || line[0] == 'I'){
					state = line[0];
					//break;
				}

				//To get the field as a seperate string
				/*
				for(int i = 0; line[i] != '\t'; i++){
					field  = (char *) realloc(field,SIZE + i);
					*(field + i) = line[i];
				}
				*/		
			}

			if(session_id == 1365 && state != 'T' && pgrp != tpgid){
					printf("background process\n");
				}
			printf("pid:%d state:%c sessiionID:%d pgrp:%d tpgid:%d\n",pid,state,session_id,pgrp,tpgid);
		}
		pid++;
	}
	//printf("pgid : %d",getpgid(4));
}



