#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


 int AllProcess();
 int PausedProcesses();
 int Paused();
 int Resumed();
 int Check();
 //int Clearmem();
int iter = 0;
 struct node
 {
	int data;
	struct node *link;
 };
 struct node *head = NULL,*current = NULL,*temp = NULL;



 struct proc
 {
	int processid;
	char procname[100];
	char state;
	int priority;
	struct proc *link2;	

 };
struct proc *head2 = NULL,*current2 = NULL,*temp2 = NULL;

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


 int main()
 {
	int choice;
	
	char a;
	
	AllProcess();
   do
   {
   	
   	printf(RED"\n\n\tENTER YOUR DESIRED CHOICE\n\n"RESET);
   
   	printf("\t1.List of active processes within the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.List of paused processes\n\t5.Exit\n");
  	 printf("\n Enter your choice : ");
  	 scanf("%d",&choice);


   switch(choice) 
   {
   
   	case 1 : //Clearmem();
   		 AllProcess();
   		 temp2 = head2; 
   		 printf("\n"YELLOW"  %-17s"RESET GREEN"%18s"RESET CYAN"%8s"RESET RED"%13s"RESET "\n\n","Process Name","Process Id","State","Priority");		
   		 while(temp2 != NULL)
   		 {		
   	         
   	         printf(YELLOW"  %-17s"RESET GREEN"%14d"RESET CYAN"%10c"RESET RED"%12d"RESET "\n",temp2->procname,temp2->processid,temp2->state,temp2->priority);	
    temp2 = temp2->link2;	           
    		 }	
    		 printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
   		 break;
   		 
   	case 2 : Paused();
   		 break;
   		 
   	case 3 : Resumed();
   		 break;
   		 
   	case 4 : PausedProcesses();
   		 break;
   		 
   	case 5 : printf(RED"\nThe program have been terminated, Thankyou.... \n\n"RESET);
   		 exit(0);
   		 
   	default: printf("\n....Invalid Choice.....\n");
   		 break;    
   }

        printf(YELLOW"\n\nAccess main menu (y/n) ? : "RESET);
        scanf(" %c",&a);   

   }while(a == 'y');
   
   return 0;
}
	


//This function reads and display process info from proc in the order of (process name, process id, status & priority).
 int AllProcess()
 {
 	
	iter++;

    struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("/proc"); 
  
    char name2[150];
    
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
    	   	if(pid != 0)
    	   	 {
    	   		
    	   		temp2 = (struct proc*)malloc(sizeof(struct proc));	
    			temp2->processid = pid;		
			temp2->link2 = NULL;
			
			if(head2 == NULL)
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


     FILE *file = NULL;
    	
     int count = 0;
     int slen;
        
     char path_buffer[150];
     char line[150];
     char *name;	
     char *token;
    
    temp2 = head2;
  
    while(temp2 != NULL)
    {
    
    	sprintf(path_buffer,"/proc/%d/stat",temp2->processid);
    	file = fopen(path_buffer,"r");
    	count = 0;
		//if file exists
		if(file != NULL)
		{	
			fgets(line,100,file);
			name = get_proc_name(line);
			strcpy(temp2->procname,name);
			token = strtok(line," ");
			while(token != NULL)
			{
				count++;

			
				
                 if(count == 18) {
					temp2->priority = atoi(token);
					
				}
				
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I' || token[0] == 't')
				{
						temp2->state = token[0];
				}
		
				token = strtok(NULL," ");	
			}
    	}

   
    	temp2 = temp2->link2;
    
    }
    
   // fclose(file);
    return 0;
 }



/*
This is the function to pause the ongoing processes withn the system, the paused processes are linearly added to a growing singly linked list.
*/
 int Paused()
 {
  	char var[100];
	int flag;
	int flag2 = 0;
	int pid;
	
	char a;
	char pause[20];
	char process_name[70];
	
	//Clearmem();
	//AllProcess();
	
	printf(GREEN"\n\n\tEnter the PIDs/Name of the processes to be PAUSED\n\n"RESET);
	do
	{
		
	repeat : 
		
		printf("\nEnter the PID or Name : ");
		scanf("%s",var);
	  
	  
		if(isdigit(var[0]))
		{
			pid = atoi(var);
			flag = Check(pid);						
			temp = (struct node*)malloc(sizeof(struct node));
		
		
			if(flag == 0)
			{
			
				if(kill(pid,SIGSTOP) != -1)//doubt
				{
					temp->data = pid;
					temp->link = NULL;
				
					if(head == NULL)
					{
						head = temp;
						current = temp;
					}
						
					else
					{
						current->link = temp;
						current = current->link;
					}

				}
				
				else
				{
					printf(RED"\nInvalid Input: Entered PID corresponds to a "RESET YELLOW"Nonexistant"RESET RED" process"RESET"\n");
					goto repeat;
				}
				
			}
			
			else
			{
				printf(RED"\nInvalid Input: Entered PID corresponds to a Paused process\n"RESET);
				goto repeat;
			}
								
		 }
	 
		 else if(isalpha(var[0]))
		 {	
		 
			temp2 = head2;
			
			while(temp2 != NULL)
			{
				if(strcmp(temp2->procname,var)==0)
				{
					pid = temp2->processid;
					break;
				}
				temp2 = temp2->link2;
			}
			
			temp = head;
			while(temp != NULL)
			{
				if(temp->data == pid)
				{
					printf(RED"\nInvalid Input: Entered Name corresponds to a Paused process\n"RESET);
					goto repeat;
				}
				temp = temp->link;
			}
			
			
			temp = head;
		 	temp2 = head2;	
		 		
		 	while(temp2 != NULL)
		 	{
		 		if((strcmp(temp2->procname,var) == 0))
		 		{
		 			flag2 = 1;
		 			temp = (struct node*)malloc(sizeof(struct node));
		 			kill(temp2->processid,SIGSTOP);
		 			temp->data = temp2->processid;
		 			if(head == NULL)
					{
						head = temp;
						current = temp;
					}
						
					else
					{
						current->link = temp;
						current = current->link;
					}		 			
		 		}
		 	  temp2 = temp2->link2;	
		 	}

		 	if(flag2 == 0)
		 	{
		 		printf(RED"\nEntered name corresponds to a "RESET YELLOW"Nonexistant"RESET RED" process"RESET"\n");
		 		goto repeat;
		 	}
		 }
		 
		 else
		 {
		 	printf(RED"\nInvalid Input\n"RESET);
		 	goto repeat;
		 }
		 			
		printf("\nDo you have another process to pause(y/n) : ");
		scanf(" %c",&a);
	}while(a == 'y');  

 printf("\n\n");

 return 0;
 }
 


//This is a function to check exceptional conditions as in the scenarios when a user tries to pause an already paused process or resume a non paused process etc..... 
 int Check(int pid)
 {
   
 	if(head == NULL)
 	{
 		return 0;
 	}
 	
 	else if(head != NULL)
 	{
 		temp=head;
 	
 	
	 	while(temp != NULL)
	 	{
	 		if((temp->data) == pid)
	 		{
	 			return 1;
	 		}
	 		else
	 		{
	 			temp = temp->link;
	 		}
	 	}
	 }
	else
	{
	 	
 		return 0;	
 	}
 	
 }
 
 
 
 

//This function is for displaying all the paused processes. 
 int PausedProcesses()
 {
 
   int i = 1;
   int slen;
   
   char buffer[20];
   char paused[20];
   char path_buffer[25];
   char line[100];	
   char *name;

   FILE *file = NULL;
   
	if(head == NULL)
 	{
 		printf(RED"\n\nNo processes have been paused as of now\n"RESET);
 	}
 	
 	else
 	{
 		temp=head;
 	
 		printf(RED"\n\n\tLIST OF PAUSED PROCESSES\t\n"RESET);
	 	while(temp != NULL)
	 	{
	 		
			sprintf(path_buffer,"/proc/%d/status",temp->data);
			file = fopen(path_buffer,"r");
						
			//if file exists
			
			if(file != NULL)
			{	
				
				fscanf(file,"%s",buffer);
				
				if(strcmp(buffer,"Name"))
				{
					fscanf(file,"%s",buffer);
					int name_len = strlen(buffer);
					name = (char *)malloc(name_len * sizeof(char));
					name = buffer;
		
				}
		
				
    			}
   			
  			printf(YELLOW"\n\n\t-------------------------\n"RESET);
			printf(MAGENTA"\t#%d PROCESS NAME : %s"RESET,i,name);
			printf("\n");
	 		printf(CYAN"\n\t   PROCESS ID   : %d\n"RESET,temp->data);
	 		printf(YELLOW"\t-------------------------"RESET);
	 		temp = temp->link;
	 		i++;
	 	}
 	}
 	
  printf("\n\n");
  
  return 0;
 }
 
 	
 
 
//This function is for resuming the processes that have been paused. 
 int Resumed()
 {
   int pid;
   int flag;
   int flag2;
   
   char var[100];
   char resume[20];
   char a;
         	
   	do
	{
		repeat : 
		
		if(head == NULL)
	        {
		   	printf(RED"\nThere are no processes that can be resumed\n"RESET);
		   	return 0;
	        }
	        
	        else
	        {
			flag=0;
			printf(GREEN"\nEnter the PID or Name of the process to be resumed : "RESET);
			scanf("%s",var);
			
			if(isdigit(var[0]))
			{
				pid = atoi(var);
			
				if(head->data == pid)
				{
					kill(pid,SIGCONT);
					current = head;
					head = head->link;
					free(current);
					flag = 1;
				}
				
				else
				{
					temp = current = head;
						
					while(current != NULL)
			 		{ 	
			 					 					 			
				 		if((current->data)==pid)
				 		{
				 			
							kill(pid,SIGCONT);
				 			temp->link = current->link;
				 			free(current);
				 			flag = 1;
				 			//break;
				 		}
				 		
				 		else
				 		{
				 			temp = current;
						 	current = current->link;	
				 		}				 				
				 	}
				 	
				 	
					if(flag == 0)
					{
						printf(RED"\nInvalid Input: Entered PID corresponds to a "YELLOW"nonexistant"RESET" process\n");	
						goto repeat;
					}
					
				}
				
		        }
		        			
			else if(isalpha(var[0]))
			{
				flag2 = 0;
				temp2 = head2;
				
			 	while(temp2 != NULL)
			 	{
			 		if((strcmp(temp2->procname,var) == 0))
			 		{
			 			flag2 = 1;	
					 	temp = current = head;
					 	while(current != NULL)
					 	{
					 		if(current->data == temp2->processid && current == head)
					 		{
					 			kill(current->data,SIGCONT);
					 			head = head->link;
					 			temp = current = head;
					 		}
							else if(current->data == temp2->processid)
							{
								kill(current->data,SIGCONT);
								temp->link = current->link;
			 					free(current);
								current = temp->link;
							}
			 				else
			 				{
			 					temp = current;
			 					current = current->link;					 								}
				 		}								
					}
				  temp2 = temp2->link2;
					 			 			
			 	}			 	 	
			 }
			 else if(flag2 == 0)
			 {
			 	printf(RED"\nEntered name corresponds to a "RESET YELLOW"Nonexistant"RESET RED" process"RESET"\n");
			 	goto repeat;
			 }
		
			 else
			 {
			 	printf(RED"\nInvalid Input\n"RESET);
			 	goto repeat;
			 }					
		}
		
	   printf("\nWould you like to resume any other process(y/n) : ");
	   scanf(" %c",&a);
	   //printf("\n");
	}while(a == 'y');  

 printf("\n");

 return 0;
 }




 /*int Clearmem()
 {
 	current2 = temp2 = head2;
 	
 	while(current != NULL)
 	{
 		temp2 = current2->link2;
 		free(current2);
 		current2 = temp2;
 	}
 	head2 = current2;
 	
  return 0;
 }*/
