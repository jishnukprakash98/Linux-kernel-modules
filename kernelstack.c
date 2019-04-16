#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	int pid=atoi(argv[1]);
	char path_buffer[100],c;
   	sprintf(path_buffer,"/proc/%d/stack",pid);
   	file = fopen(path_buffer,"r");
	c = fgetc(file); 
   	while (c != EOF) 
   	{ 
        	printf ("%c", c); 
        	c = fgetc(file); 
    	} 
  
   	fclose(file);
    	return 0;
}

