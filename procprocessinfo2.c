//akhil gokuldas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h> 


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


 struct proc
 {
	int processid;
	struct proc *link2;	

 };
 struct proc *head2=NULL,*current2=NULL,*temp2=NULL;
  
  
  
//The main program begins here

int main()
{
//inserting code1

 struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("/proc"); 
  
    char name2[100];
    
    int pid;
    
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
        printf("Could not open current directory" ); 
        return 0; 
    } 
  
    while ((de = readdir(dr)) != NULL) 
    	{
    	   
    	   	strcpy(name2,de->d_name);
    	   	pid = atoi(name2);
    	   	if(pid!=0)
    	   	 {
    	   		
    	   		temp2=(struct proc*)malloc(sizeof(struct proc));			
    	   		temp2->processid=pid;
			temp2->link2=NULL;
			
			if(head2==NULL)
			 {
				head2 = temp2;
				current2 = temp2;
			 }
			 	
			else
			 {
				current2->link2 = temp2;
				current2 = current2->link2;
			 }
		
		
		 }
    	   		
             }
              
closedir(dr);     
//code 1 finished



    FILE *file = NULL;
    
	char path_buffer[25];
	
	char line[10];
	
	char *name;
	
	char state;
	
	char *token;
    
	int count = 0;
	
	int pgrp = 0;
	
	int tpgid = 0;
	
	int priority=0;
    
        int utime=0;
        
        int slen;
         
        int z;
    
        long long unsigned int starttime = 0;
    
    
    //scanning for the particular file with the input pid......
    temp2=head2;
    while(temp2!=NULL)
    {
    
    	sprintf(path_buffer,"/proc/%d/stat",temp2->processid);
    	file = fopen(path_buffer,"r");
    	count = 0;
		//if file exists
		if(file != NULL)
		{	
			fgets(line,100,file);
			token = strtok(line," ");
			while(token != NULL)
			{
				count++;
				
				//to get the process name
				if(count == 2)
				{
					int name_len = strlen(token);
					name = (char *)malloc(name_len * sizeof(char));
					name = token;
					//strncpy(name,token,name_len);
					//to get the process state
				}
                              if(count == 18){
					priority = atoi(token);
					
				}
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I')
				{
						state = token[0];
				}
		
				token = strtok(NULL," ");	
			}
    		}
   
    	slen=strlen(name);
    	for (z = 1; z <= slen-1; z++)
    	{
      	  name[z-1] = name[z];
    	}
    	name[slen-2]='\0';
  
    	printf(YELLOW"%-17s"RESET GREEN"%14d"RESET CYAN"%10c"RESET RED"%12d"RESET "\n",name,temp2->processid,state,priority);
    
    	temp2=temp2->link2;
    	}
    
    return 0;
}










