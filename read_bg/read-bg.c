/* Akhileswar*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>

#include "llist.h"

//#define PROC_LIMIT 32768

static char* get_proc_name(char *str)
{
		int i = 0;

		char *name = strchr(str,'(') + 1;
		for(i = 0; name[i] != ')'; i++);
		char *n = (char *)malloc((i+1) * sizeof(char));
		
		strncpy(n,name,i);
		n[i] = '\0';

	return n;
}


int main(int argc, char *argv[])
{
	
	FILE *file = NULL;
	static char path_buffer[25];
	static int pid = 2;
	static char line[100];
	static char *token;
	static char *name;
	static char state;
	static int count = 0;
	static int pgrp = 0;
	static int tpgid = 0;
	static int session_id = 0;

	struct dirent *dir_entry;
	DIR           *dir;

	node *my_list = list_create(0);
	
	printf("Background process BELOW:\n");

	dir = opendir("/proc/");
	if (dir == NULL) {
		perror("opendir");
		return 1;
	}

	while (dir_entry = readdir(dir)) {
		if (dir_entry->d_name[0] <= '9' && dir_entry->d_name[0] >= '0') {
			pid = atoi(dir_entry->d_name);
			
			sprintf(path_buffer,"/proc/%d/stat",pid);
		
			file = fopen(path_buffer,"r");
		
			if(file != NULL){
			  
				count = 0;
				
				fgets(line,100,file);
				name = get_proc_name(line);
				
				token = strtok(line," ");
				while(token != NULL){
					count++;
			
					if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I') {
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
				if(session_id == 17041 && state != 'T' && pgrp != tpgid) {
					
					//printf("pid:%d %s state:%c sessionID:%d pgrp:%d tpgid:%d\n",pid,name,state,session_id,pgrp,tpgid);
					list_push(my_list,pid);
					printf("pid:%5d %-30s Session: %5d \n",pid,name,session_id);
					//kill(pid, SIGQUIT);	
			}
			fclose(file);
			
		}


	}
	}
		list_print(my_list);
	
	//printf("UID : %d",getuid());
	return 0;
}

