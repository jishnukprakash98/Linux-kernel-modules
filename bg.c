#include <stdio.h>

//#define path "/proc/"

int main(){
	
	FILE *file = NULL;
	char path_buffer[15];
	int pid = 0;
	char line[50];
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
			}
		}
		
		pid++;
	}
		
	return 0;
}
