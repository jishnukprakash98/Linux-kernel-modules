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
	char line[100];
	char *token;
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
	
	while(pid < 32768){
		sprintf(path_buffer,"/proc/%d/stat",pid);
		
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
			count = 0;
			
				fgets(line,100,file);
				token = strtok(line," ");
				while(token != NULL){
				count++;
				
				//to get the process name
				if(count == 2){
					int name_len = strlen(token);
					name = (char *)malloc(name_len * sizeof(char));
					name = token;
					//strncpy(name,token,name_len);
					//to get the process state
				
					
				}
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I'){
						state = token[0];
					
				}
				if(count == 5){
					pgrp = atoi(token);
				}
				if(count == 6){
					session_id = atoi(token);
				}
				if(count == 8){
					tpgid = atoi(token);
					break;
				}

				

				//To get the field as a seperate string
				/*
				for(int i = 0; line[i] != '\t'; i++){
					field  = (char *) realloc(field,SIZE + i);
					*(field + i) = line[i];
				}
				*/	
				token = strtok(NULL," ");	
			}//token!=NULL
			printf("pid:%d %s state:%c sessionID:%d pgrp:%d tpgid:%d\n",pid,name,state,session_id,pgrp,tpgid);
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
