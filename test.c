#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<unistd.h> 
#include "uthash.h"

struct my_struct {
    float usage;            /* we'll use this field as the key */
    char process_name[10];
    UT_hash_handle hh; /* makes this structure hashable */
};
struct my_struct *process = NULL;




void add_process(struct my_struct *s) {
    HASH_ADD_INT( process, usage, s );
}

void Read_val(){
	FILE *file;
	float use = 0.0;
	char proc[50];
	file=fopen("/tmp/cpu_usage.txt","r");
	
	while(!feof(file)){
		fscanf(file, "%s %f",proc,&use);
		struct my_struct *process = (struct my_struct*)malloc(sizeof(struct my_struct));
		process->usage = use;
		strcpy(process->process_name,proc);
		
		printf("\n %-10s \t %8g ",proc,use);
		add_process(process);
		//printf("process : %s \tusage: %d\n",process->process_name,process->usage);
	}
	fclose(file);		
}

int main(){
int i,secs=60;
int unit_time=10;
int steps=secs/unit_time;
printf("Watching CPU usage... ");
for(i=0;i<steps;i++)
{
system( "ps -eocomm,pcpu | tail -n +2 >> /tmp/cpu_usage.txt");
//sleep(unit_time);
printf("CPU Eaters");
//system("cat /tmp/cpu_usage.txt  ");



Read_val();
return 0;
}}
