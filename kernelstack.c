#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	int pid=atoi(argv[1]);
	int i=0;
	char path_buffer[100],c[25],stor[100][25];
   	sprintf(path_buffer,"/proc/%d/stack",pid);
   	file = fopen(path_buffer,"r");
	fgets(c,25,file); 
   	while (!feof(file)) 
   	{ 
		sprintf(stor[i],"%s",c);
		printf("%s",stor[i]);		
		i++;         	
		fgets(c,25,file); 
    	} 
  
   	fclose(file);
    	return 0;
}

