#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h> 
//#include <cstdio.h>




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
    	   // if(isalpha(de->d_name))
    	   	strcpy(name2,de->d_name);
    	   	pid = atoi(name2);
    	   	if(pid!=0)
    	   	 {
    	   		//trial
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
    	   		//trial    	   		   	   		
       	   		
            		//printf("%d\n", pid); 
             }
              
closedir(dr);     
//code 1 finished



    FILE *file = NULL;
    
	char path_buffer[25];
	
	char line[10];
	
	char *name;
	
	char state;
	
	char *token;
	char *prev;
	
        //int pid=atoi(argv[1]);
    
	int count = 0;
	
	int pgrp = 0;
	
	int tpgid = 0;
	
	int priority=0;
    
        int utime=0;
    
        long long unsigned int starttime = 0;
    
   // char split[1] = '\0'; 
    
    //scanning for the particular file with the input pid......
    temp2=head2;
    while(temp2!=NULL)
    {
    
    	sprintf(path_buffer,"/proc/31212/stat");
    	file = fopen(path_buffer,"r");
    	count = 0;
    
    	fgets(line,100,file);

	token = strtok(line," ");
	while(token != NULL){
		count++;
				
				//to get the process name
		if(count == 2){
			int name_len = strlen(token);
			name = (char *)malloc(name_len * sizeof(char));
			token[name_len - 2] = '\0';  // to remove end ')'
			name = token+1;		     // skip first '('
			if(isalpha(prev[2]))
				strcat(prev,name);
			
			prev = name;
			
			//memcpy(name,token,name_len);
			//to get the process state
		}
		if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I'){
						state = token[0];
				}
				/*
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
			*/
				

				//To get the field as a seperate string
				/*
				for(int i = 0; line[i] != '\t'; i++){
					field  = (char *) realloc(field,SIZE + i);
					*(field + i) = line[i];
				}
				*/	
				token = strtok(NULL," ");	
	}//token!=NULL
    
     //printf("%-12%s%-12%d%-12%c%-12%d \n",name,temp2->processid,state,priority);
    //printf("%.20s %.12s %.20s %12s","process name", "process id", "state", "priority"); 
    printf("%-16s %14d  %-20c %12d \n",name,temp2->processid,state,priority);
    
    temp2=temp2->link2;
    }
    
    return 0;
}







