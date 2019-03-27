/* Akhileswar*/

// To run provide $$ as argument

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[])
{
	
	FILE *file = NULL;
	char path_buffer[25];
	int pid = 2;
	char line[10];
	
	char *name;
	char state;
	int count = 0;
	int pgrp = 0;
	int tpgid = 0;
	int session_id = 0;
	//int call_pid = getpid();
	//int call_sid = getsid(call_pid);
	if(argc < 2){
		printf("Supply argument\n");
		return 0;	
	}
	printf("current shell PID:%s\n",argv[1]);
	
	while(pid < 10000){
		sprintf(path_buffer,"/proc/%d/stat",pid);
		
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
			count = 0;
			while(fscanf(file,"%s",line)){
				
				count++;

				//to get the process name
				if(line[0] == '('){
					int len = strlen(line);
					name = (char *)malloc(len * sizeof(char));
					strncpy(name,line,len);
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
			//Distinguishing background processes
			if(session_id == atoi(argv[1]) && state != 'T' && pgrp != tpgid){
					printf("background process BELOW\n");
					printf("pid:%d %s state:%c sessionID:%d pgrp:%d tpgid:%d\n",pid,name,state,session_id,pgrp,tpgid);
					//kill(pid, SIGQUIT);	
			}
			
		}
		pid++;
	}
	//printf("pgid : %d",getpgid(4));
}


