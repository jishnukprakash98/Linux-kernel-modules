#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"


//The structure definition for the linked list
 struct node
 {
	int data;
	struct node *link;
 };
 struct node *head=NULL,*current=NULL,*temp=NULL;



//List of functions used with in the program
 int AllProcess();
 int PausedProcesses();
 int Paused();
 int Resumed();
 int Check();


//The main function begins here
 int main()
 {

	char a;
	int choice;
	
   do
   
   {

   printf(RED"\n\n\tENTER YOUR DESIRED CHOICE\n\n"RESET);
   
   printf("\t1.List of active processes with in the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.List of paused processes\n\t5.Exit\n");
   printf("\n Enter your choice : ");
   scanf("%d",&choice);

   switch(choice)
   {
   	case 1 : AllProcess();
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

        printf(YELLOW"\n\nAccess main menu (y/n) ? :"RESET);
        scanf(" %c",&a);   

   }while(a=='y');
}
	





 int AllProcess()
 {
	printf(BLUE"\n\n\t\tTHE LIST OF ALL PROCESSES IN THE SYSTEM\n\n"RESET);
	system("ps all");     

 }




//This is the function to pause the ongoing processes withn the system, the paused processes are linearly added to a growing singly linked list.
 int Paused()
 {
  
	int pid;
	int i=0;
	int flag;
	char a;
	char pause[20];
	
	printf(GREEN"\n\n\tEnter the PIDs of the processes to be PAUSED\n\n"RESET);
	do
	{
	
		repeat : 
		
		printf("\nEnter the PID : ");
		scanf("%d",&pid);

		flag=Check(pid);//function call to check whether the process is already paused
				
		temp=(struct node*)malloc(sizeof(struct node));
		if(flag==0)
		{
			temp->data=pid;
			temp->link=NULL;
			sprintf(pause,"kill -STOP %d",temp->data);  
			system(pause);
			if(head==NULL)
			{
				head=temp;
				current=temp;
			}	
			else
			{
				current->link=temp;
				current=current->link;
			}
		
			printf("\nDo you have another process to pause(y/n) : ");
			scanf(" %c",&a);
		}
		else
		{
			printf(RED"\nInvalid Input: Entered PID corresponds to a Paused process\n"RESET);
			goto repeat;
		}	
	}while(a=='y');  

 printf("\n\n");

 }
 



 
 int Check(int pid)
 {
   
 	if(head==NULL)
 	{
 		return 0;
 	}
 	
 	else if(head!=NULL)
 	{
 		temp=head;
 	
 	
	 	while(temp!=NULL)
	 	{
	 		if((temp->data)==pid)
	 		{
	 			return 1;
	 		}
	 		else
	 		{
	 			temp=temp->link;
	 		}
	 	}
	 }
	else
	{
	 	
 		return 0;	
 	}
 }
 
 
 
 

 
 int PausedProcesses()
 {
 
   int i=1;
   
 	if(head==NULL)
 	{
 		printf(RED"\n\nNo processes have been paused as of now\n"RESET);
 	}
 	
 	else
 	{
 		temp=head;
 	
 		printf(RED"\n\tLIST OF PAUSED PROCESSES\t\n"RESET);
	 	while(temp!=NULL)
	 	{
	 		printf(CYAN);
	 		printf("\nPROCESS #%d : %d",i,temp->data);
	 		printf(RESET);
	 		temp=temp->link;
	 		i++;
	 	}
 	}
 	
  printf("\n\n");
  
 }
 
 	
 
 
 
 int Resumed()
 {
   char resume[20];
   char a;
   int pid;
   int flag;
   
   	
   	do
	{
		repeat : 
		
		if(head==NULL)
	        {
		   	printf(RED"\nThere are no processes that can be resumed\n"RESET);
		   	return 0;
	        }
	        
	        else
	        {
		
			flag=0;
			printf(GREEN"\nEnter the PID of the process to be resumed : "RESET);
			scanf("%d",&pid);
			
			if(head->data==pid)
			{
				sprintf(resume,"kill -CONT %d",head->data);  
				system(resume);
				current=head;
				head=head->link;
				free(current);
			}
			
			else
			{
						
				temp=current=head;
					
				while(current!=NULL)
		 		{
			 	
			 			
			 		if((current->data)==pid)
			 		{
			 			sprintf(resume,"kill -CONT %d",current->data);  
						system(resume);
			 			temp->link=current->link;
			 			free(current);
			 			flag=1;
			 			break;
			 		}
			 		else
			 		{
			 			temp=current;
					 	current=current->link;	
			 		}
			 				
			 	}
			 	
			 	
		 	
				if(flag==0)
				{
					printf(RED"\nInvalid Input: Entered PID corresponds to a nonexistant process\n"RESET);	
					goto repeat;
				}
				else
				{	
					printf(YELLOW"\nDo you have another process to resume(y/n) : "RESET);
					scanf(" %c",&a);
				}	
		        }
		}
	}while(a=='y');  

 printf("\n\n");

 
 
 }



