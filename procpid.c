#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    FILE *file = NULL;
	char path_buffer[25];
	char line[10];
	char *name;
	char state;
    int pid=atoi(argv[1]);
	int count = 0;
	int pgrp = 0;
	int tpgid = 0;
    int priority=0;
    int utime=0;
    long long unsigned int starttime = 0;
    sprintf(path_buffer,"/proc/%d/stat",pid);
    file = fopen(path_buffer,"r");
    	count = 0;
			while(fscanf(file,"%s",line))
            {
				
				count++;
				if(line[0] == '('){
					int len = strlen(line);
					name = (char *)malloc(len * sizeof(char));
					strncpy(name,line,len);
				}
				if(count == 5){
					pgrp = atoi(line);
				}
				if(count == 8){
					tpgid = atoi(line);
				}
                if(count == 18){
					priority = atoi(line);
				}
                if(count == 14){
					pgrp = atoi(line);
				}
				if(line[0] == 'S' || line[0] == 'R' || line[0] == 'T' || line[0] == 'I'){
					state = line[0];
				}
                if(count == 22){
					starttime = atoi(line);
                    break;
                }
            }
    printf("pid:%d %s state:%c priority:%d starttime:%llu utime:%d pgrp:%d tpgid:%d\n",pid,name,state,priority,starttime,utime,pgrp,tpgid);
    return 0;
}
