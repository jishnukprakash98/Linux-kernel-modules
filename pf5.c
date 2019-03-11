#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//The structure definition for the linked list
 struct node
 {
	int data;
	struct node *link;
 };
 struct node *head=NULL,*current=NULL,*temp=NULL;



//List of functions used with in the program
 int AllProcess();
 int PausedProcess();
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

   printf("\n\n........................................ENTER YOUR DESIRED CHOICE...........................................\n\n");
   
   printf("\t1.List of active processes with in the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.List of paused processes\n");
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
   	case 4 : Check();
   		 break;
   	default: printf("\n....Invalid Choice.....\n");
   		 break;    
   }

        printf("\n\nDo you want to continue (y/n) ? :");
        scanf(" %c",&a);   

   }while(a=='y');
}
	






 int AllProcess()
 {
	printf("\n\n====================================THE LIST OF ALL PROCESSES IN THE SYSTEM===================================\n\n");
	system("ps all");     

 }




 int Paused()
 {
  
	int pid;
	int i=0;
	int flag;
	char a;
	char pause[20];
	
	printf("\n\n.....................Enter the PIDs of the processes to be PAUSED........................\n\n");
	do
	{
		temp=(struct node*)malloc(sizeof(struct node));
		
		repeat : 
		printf("\nEnter the PID : ");
		scanf("%d",&pid);
		
		flag=Check(pid);//need function call to check whether the process is already paused
		
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
			printf("\nInvalid Input: Entered PID corresponds to an already Paused process\n");
			goto repeat;
		}	
	}while(a=='y');  

 printf("\n\n");

 }
 


 
 int PausedProcesses()
 {
 
   int i=1;
   
 	if(head==NULL)
 	{
 		printf("\n\nNo processes have been paused as of now\n");
 	}
 	
 	else
 	{
 		temp=head;
 	}
 	
 	while(temp!=NULL)
 	{
 		printf("\nPROCESS #%d : %d",i,temp->data);
 		temp=temp->link;
 		i++;
 	}
 	
  printf("\n\n");
  
 }
 
 
 
 
 int Check(int pid)
 {
   
 	if(head==NULL)
 	{
 		return 0;
 	}
 	
 	else
 	{
 		temp=head;
 	}
 	
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
 	
 	return 0;	
 		
 }
 	
 
 
 
 int Resumed(char resume[20])
 {
   char a;
   int pid;
   int flag=0;
   
   
   	do
	{
		
		if(head==NULL)
	        {
		   	printf("\nThere are no processes that can be resumed\n");
		   	return 0;
	        }
	        
	        else
	        {
		
			repeat : 
			printf("\nEnter the PID of the process to be resumed : ");
			scanf("%d",&pid);
						
			temp=current=head;
				
			while(current!=NULL)
	 		{
		 		temp=current;
		 		current=current->link;
		 			
		 		if(current->data==pid)
		 		{
		 			sprintf(resume,"kill -CONT %d",current->data);  
					system(resume);
		 			temp->link=current->link;
		 			free(current);
		 			flag=1;
		 			break;
		 		}
		 				
		 	}
	 	
			if(flag==0)
			{
				printf("\nInvalid Input: Entered PID corresponds to a nonexistant process\n");	
				goto repeat;
			}
			else
			{	
				printf("\nDo you have another process to resume(y/n) : ");
				scanf(" %c",&a);
			}	
		}
	}while(a=='y');  

 printf("\n\n");

 
 
 }

