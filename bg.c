/* Akhileswar*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define PROC_LIMIT 32768

static char* get_proc_name(char *str, char *name)
{
		int i = 0;

		name = strchr(str,'(') + 1;
		for(i = 0; name[i] != ')'; i++);
		char *n = (char *)malloc(i * sizeof(char));
		
		strncpy(n,name,i);

	return n;
}


int main(int argc, char *argv[])
{
	
	FILE *file = NULL;
	char path_buffer[25];
	int pid = 2;
	char line[100];
	char *token;
	char *name;
	char state;
	int s = atoi(argv);
	int count = 0;
	int pgrp = 0;
	int tpgid = 0;
	int session_id = 0;
	
	while(pid < PROC_LIMIT){
		sprintf(path_buffer,"/proc/%d/stat",pid);
		
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
			count = 0;
				
			fgets(line,100,file);
				
			name = get_proc_name(line,name);

			token = strtok(line," ");
			while(token != NULL){
			count++;
			
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I'){
						state = token[0];
				}
				else if(count == 5){
					pgrp = atoi(token);
				}
				else if(count == 6){
					session_id = atoi(token);
				}
				else if(count == 8){
					tpgid = atoi(token);
					break;
				}

				token = strtok(NULL," ");	
			}
			
			//Distinguishing background processes
			if(session_id==s state != 'T' && pgrp != tpgid){
					printf("background process BELOW\n");
					//printf("pid:%d %s state:%c sessionID:%d pgrp:%d tpgid:%d\n",pid,name,state,session_id,pgrp,tpgid);
					printf("pid:%d %s \n",pid,name);
					//kill(pid, SIGQUIT);	
			}
			
		}
			
		
		pid++;
	}
	//printf("UID : %d",getuid());
}
