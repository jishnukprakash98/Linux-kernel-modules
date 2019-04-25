/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/tty.h>
#include <linux/llist.h>
#include <linux/spinlock.h>
#include <asm/uaccess.h> 
#include <linux/slab.h>
#include <linux/moduleparam.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define Bwhite  "\x1b[44;1m"


 int AllProcess();
 int PausedProcesses();
 int Paused();
 int Resumed();
 int Check();
 int Clearmem();



 struct node
 {
 
	int data;
	//struct node *link;
	struct list_head p_list ;
 };
 struct node *head = NULL,*current = NULL,*temp = NULL;



 struct proc
 {
 
	int processid;
	char procname[100];
	char state;
	int priority;
	struct list_head a_list ;

 };
struct proc *head2 = NULL,*current2 = NULL,*temp2 = NULL;


/*
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
*/


static int __init start_program(void)
 {
 
	int choice;
	
	char a;
	
	AllProcess();
	
   do
   {
   	
   	printk(RED"\n\n\tENTER YOUR DESIRED CHOICE\n\n"RESET);
   
   	printk("\t1.List of active processes within the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.List of paused processes\n\t5.Exit\n");
  	 printk("\n Enter your choice : ");
  	 scanf("%d",&choice);


	   switch(choice) 
	   {
	   
	   	case 1 : Clearmem();
	   		 AllProcess();
	   		 
	   		 temp2 = head2; 
	   		 
	   		 printk("\n"YELLOW Bwhite"  %-17s"RESET GREEN Bwhite"%18s"RESET CYAN Bwhite"%8s"RESET RED Bwhite"%13s"RESET "\n\n","Process Name","Process Id","State","Priority");		
	   		 while(temp2 != NULL)
	   		 {		
	   	         
	   	         	printk(YELLOW"  %-17s"RESET GREEN"%14d"RESET CYAN"%10c"RESET RED"%12d"RESET "\n",temp2->procname,temp2->processid,temp2->state,temp2->priority);	
	    temp2 = temp2->link2;	           
	    		 }
	    		 printk("\n"Bwhite"-------------------------------------------------------"RESET"\n");	
	   		 break;
	   		 
	   		 
	   	case 2 : Paused();
	   		 break;
	   		 
	   		 
	   	case 3 : Resumed();
	   		 break;
	   		 
	   		 
	   	case 4 : PausedProcesses();
	   		 break;
	   		 
	   		 
	   	case 5 : printk(RED"\nThe program have been terminated, Thankyou.... \n\n"RESET);
	   		 exit(0);
	   		 
	   		 
	   	default: printk("\n....Invalid Choice.....\n");
	   		 break;    
	   }


    printk(YELLOW "\n\nAccess main menu (y/n) ? : "RESET);
    scanf(" %c",&a);   

   }
   while(a == 'y');
   
   return 0;
   
}
	

	struct task_struct	*task;
	//size_t			bg_proc_count = 0;
	pid_t			pid;
	char			state;
	int			normal_prio;


	/* kernel linked list tryout*/
	struct node *p;
	struct node *curr;
	struct list_head test_head;
	struct list_head *ptr;

	INIT_LIST_HEAD(&test_head);

	p = kmalloc(sizeof(struct node *),GFP_KERNEL);
	p->data = 999;
	list_add(&p->test_list,&test_head);


	for_each_process(task) 
	{
		
		state = task_state_to_char(task);
		normal_prio = task->normal_prio;
		
	/*	
		sprintf(path_buffer,"/proc/%d/stat", task->pid);
		printk(KERN_INFO "%s\n",path_buffer);
			
		fil = filp_open(path_buffer, O_RDONLY, 0);
		
		if(fil == NULL)
       		 	printk(KERN_ALERT "rb: filp_open error!!.\n");
    		else 
    		{
			// Get current segment descriptor
			fs = get_fs();
			// Set segment descriptor associated to kernel space
			set_fs(get_ds());
			// Read the file
			size = fil->f_op->read(fil, buf, 128, &fil->f_pos);
			// Restore segment descriptor
			set_fs(fs);
			// See what we read from file
			buf[size] = '\0';
			//printk(KERN_INFO "rb: buf : %s\n", buf);
		}
		if (fil != NULL)
			filp_close(fil, NULL);

		
		
	*/

		
				//force_sig(SIGSTOP,task);
	}

//This function reads and display process info from proc in the order of (process name, process id, status & priority).
 /*int AllProcess()
 {
 		
    struct dirent *de;  // Pointer for directory entry 
  
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir("/proc"); 
  
    char name2[150];
    
    int pid;
    
    if (dr == NULL)  // opendir returns NULL if couldn't open directory 
    { 
    
        printk("Could not open current directory" ); 
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
				
                 		if(count == 18) 
                 		{
					temp2->priority = atoi(token);
				for_each_process(task) {
		pgrp = pid_vnr(task_pgrp(task));
		session_id = pid_vnr(task_session(task));
		state = task_state_to_char(task);
		
		sprintf(path_buffer,"/proc/%d/stat", task->pid);
		//printk(KERN_INFO "%s\n",path_buffer);
			
		fil = filp_open(path_buffer, O_RDONLY, 0);
		
		if(fil == NULL)
       		 	printk(KERN_ALERT "rb: filp_open error!!.\n");
    		else {
			// Get current segment descriptor
			fs = get_fs();
			// Set segment descriptor associated to kernel space
			set_fs(get_ds());
			// Read the file
			size = fil->f_op->read(fil, buf, 128, &fil->f_pos);
			// Restore segment descriptor
			set_fs(fs);
			// See what we read from file
			buf[size] = '\0';
			//printk(KERN_INFO "rb: buf : %s\n", buf);
		}
		if (fil != NULL)
			filp_close(fil, NULL);

		tpgid = 0;
		/* Get tpgid (8th field sep by ' ') from stat file. */
		while (i < 128) {
			if (buf[i] == ' ') {
				if (j == 7)
					break; /* If reached 8th ' '. */
				++j; /* j is no: of spaces read. */
				++i;
				continue;
			}
			if (j == 7 && buf[i] != ' ') {
				if (buf[i] == '-') { /* -ve valued read. */
					tpgid = -1; /* No tpgid. */
					break;
				}
				else	/* Convert to number. */
					tpgid = tpgid * 10 + (buf[i] - '0');
			}
			++i;
		}
		i = j = 0;


		if(state != 'T' && pgrp != tpgid) {
		
			//Background process
			printk(KERN_INFO " Background %5d  %16s",task->pid,task->comm);
			pids[bg_proc_count++] = task->pid;
			
			if(task->pid == input)
				force_sig(SIGSTOP,task);
		} 
	}		
				}
				
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I' || token[0] == 't')
				{
					temp2->state = token[0];
				}
		
				token = strtok(NULL," ");	
			}
    	}

   
    	temp2 = temp2->link2;
    	fclose(file);
    }
    
   // 
    rewind(file);
    
    return 0;
    
 }

*/

/*
This is the function to pause the ongoing processes withn the system, the paused processes are linearly added to a growing singly linked list.
*//*
 int Paused()
 {
 
  	char var[100];
	int flag;
	int flag2;
	int pid;
	
	char a;
	char pause[20];
	char process_name[70];
	
	Clearmem();
	AllProcess();
	
	printk(GREEN"\n\n\tEnter the PIDs/Names of the processes to be PAUSED\n\n"RESET);
	do
	{
		
	//repeat : 		
		flag2 = 0;
		
		printk(CYAN"\nEnter the PID or Name : "RESET);
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
				
					printk(RED"\nInvalid Input: Entered PID corresponds to a "RESET YELLOW"Non-existing"RESET RED" process"RESET"\n");
					//goto repeat;
				}
				
			}
			
			else
			{
			
				printk(RED"\nInvalid Input: Entered PID corresponds to a Paused process\n"RESET);
				//goto repeat;
			}
								
		 }
	 
		 else if(isalpha(var[0]))
		 {	
		 
			temp2 = head2;
			
			while(temp2 != NULL)
			{
			
				if(strcmp(temp2->procname,var)==0)
				{
					flag2 = 1;
					pid = temp2->processid;
					break;
				}
				temp2 = temp2->link2;
			}
			
			temp = head;
			
			if(flag2 == 1)
			{
			
				while(temp != NULL)
				{
				
					if(temp->data == pid)
					{
					
						printk(RED"\nInvalid Input: Entered Name corresponds to a Paused process\n"RESET);
						goto ask;
					}
					temp = temp->link;
				}			
			}
			
			temp = head;
		 	temp2 = head2;	
		 	flag2 = 0;
		 		
		 	while(temp2 != NULL)
		 	{
		 	
		 		if((strcmp(temp2->procname,var) == 0))
		 		{
		 		
		 			flag2 = 1;
		 			temp = (struct node*)malloc(sizeof(struct node));
		 			kill(temp2->processid,SIGSTOP);
		 			temp->data = temp2->processid;
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
		 	  temp2 = temp2->link2;	
		 	}

		 	if(flag2 == 0)
		 	{
		 		
		 		printk(RED"\nEntered name corresponds to a "RESET YELLOW"Non-existing"RESET RED" process"RESET"\n");
		 		//goto repeat;
		 	}
		 }
		 
		 else
		 {
		 
		 	printk(RED"\nInvalid Input : "RESET"The input doesn't represent a valid Process Name or ID\n");
		 	//goto repeat;
		 }
		 			
	ask:	printk("\nDo you have any other process to pause(y/n) : ");
		scanf(" %c",&a);
	}while(a == 'y');  

 printk("\n");

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
 	
 		printk(RED"\n\nNo processes have been paused as of now\n"RESET);
 	}
 	
 	else
 	{
 	
 		temp=head;
 	
 		printk(RED"\n\n\tLIST OF PAUSED PROCESSES\t\n"RESET);
 		
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
   			
  			printk(YELLOW"\n\n\t-------------------------\n"RESET);
			printk(MAGENTA"\t#%d PROCESS NAME : %s"RESET,i,name);
			printk("\n");
	 		printk(CYAN"\n\t   PROCESS ID   : %d\n"RESET,temp->data);
	 		printk(YELLOW"\t-------------------------"RESET);
	 		temp = temp->link;
	 		i++;
	 	}
 	}
 	
  printk("\n\n");
  
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
		//repeat : 
		
		if(head == NULL)
	        {
	        
		   	printk(RED"\nThere are no processes that can be resumed\n"RESET);
		   	return 0;
	        }
	        
	        else
	        {
	        
			flag=0;
			printk(GREEN"\nEnter the PID or Name of the process to be resumed : "RESET);
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
					
						printk(RED"\nInvalid Input: Entered PID corresponds to a "YELLOW"Non-existing"RESET" process\n");	
						//goto repeat;
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
			 			 
				 if(flag2 == 0)
				 {
				 
				 	printk(RED"\nEntered name corresponds to a "RESET YELLOW"Non-existing"RESET RED" process"RESET"\n");
				 	//goto repeat;
				 }
			
			 }
			 
			 else
			 {
			 
			 	printk(RED"\nInvalid Input : "RESET"The input doesn't represent a valid Process Name or ID\n");//printk(RED"\nInvalid Input\n"RESET);			 	
			 	//goto repeat;
			 }					
		}
		
	   printk("\nWould you like to resume any other process(y/n) : ");
	   scanf(" %c",&a);
	   //printk("\n");
	}
	while(a == 'y');  

 printk("\n");

 return 0;
 
 }



 int Clearmem()
 {
 
 	current2 = temp2 = head2;
 	
 	while(current2 != NULL)
 	{
 	
 		temp2 = current2->link2;
 		free(current2);
 		current2 = temp2;
 	}
 	head2 = current2;
 	
  return 0;
  
 }

static void __exit stop_program(void)
{
        
        printk(KERN_INFO "\nFINISHED TESTING...\n");
}

module_init(start_program);
module_exit(stop_program);
*/

