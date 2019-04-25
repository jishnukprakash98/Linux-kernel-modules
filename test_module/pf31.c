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
#include <linux/spinlock_types.h>
#include <asm/uaccess.h> 
#include <linux/slab.h>
#include <linux/moduleparam.h>





MODULE_AUTHOR("AKG");
MODULE_LICENSE("GPL");
/*
 int AllProcess();
 int PausedProcesses();
 int Paused();
 int Resumed();
 int Check();
 int Clearmem();

*/

rwlock_t list_lock; //The definition of read and write lock, lock before operation, after operation.

static DEFINE_RWLOCK(myrwlock);
 struct node
 {

	int data;
	//struct node *link;
	struct list_head p_list ;
 };
 //struct node *head = NULL,*current = NULL,*temp = NULL;



 struct proc
 {

	int processid;
	char procname[100];
	char state;
	int priority;
	struct list_head a_list ;

 };
//struct proc *head2 = NULL,*current2 = NULL,*temp2 = NULL;


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
	struct task_struct	*task;
	pid_t			pid;
	//char			state;
	//int			normal_prio;
	
	struct proc *p;
	struct proc *curr,*temp;
	//struct list_head test_head;
	struct list_head *ptr;

	//INIT_LIST_HEAD(&test_head);
	LIST_HEAD(test_head);
	
	p = kmalloc(sizeof(struct proc *),GFP_KERNEL);
	p->processid = 1;//task->pid ;
	strcpy(p->procname,"neelan") ;
	p->state ='R';//task->state ;
	p->priority = 0;//task->normal_prio ;

	write_lock(&list_lock);
	list_add(&p->a_list,&test_head);
	 write_unlock(&list_lock);
	
	write_lock(&list_lock);
	list_for_each_entry(curr, &test_head, a_list)
    	{
        	printk(KERN_INFO "Testing:%d\n",curr->processid);
    	}
    	 write_unlock(&list_lock);
	for_each_process(task) 
	{

		


		
	


				//force_sig(SIGSTOP,task);
	}
	write_lock(&list_lock);
	 list_for_each_entry_safe(curr,temp,&test_head,a_list)
	 {
	 	printk(KERN_INFO "EJECTING %s",curr->procname);
	 	
	 	list_del(&curr->a_list);
        	kfree(curr);
	 }
	 write_unlock(&list_lock);
	
	
	

  
  

}


	


	
	

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
 */
static void __exit stop_program(void)
{
        
        printk(KERN_INFO "\nFINISHED TESTING...\n");
}
module_init(start_program);
module_exit(stop_program);



