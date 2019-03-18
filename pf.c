#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 struct node
 {
	int data;
	struct node *link;
 };
 struct node *head=NULL,*current=NULL,*temp=NULL;


 int AllProcess();
// int PausedProcess();
 int Paused();
// int Resumed();
// int FindProcess();


 int main()
 {

	
	char pause[20]; 
	char resume[20];
	char a;
	int choice;
	int pid;
	
	
   do
   
   {

   printf("\n\n.....................ENTER YOUR DESIRED CHOICE.......................\n\n");
   
   printf("\t1.List of active processes with in the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.List of paused processes\n");
   printf("\n Enter your choice : ");
   scanf("%d",&choice);

   switch(choice)
   {
   	case 1 : AllProcess();
   		 break;
   	case 2 : Paused(pause);
   		 break;
   	//case 3 : Resumed();
   	//	 break;
   	//case 4 : PausedProcess();
   	//	 break;
   	default: printf("\n....Invalid Choice.....\n");
   		 break;    
   }

        printf("Do you want to continue (y/n) ? :");
        scanf(" %c",&a);   

   }while(a=='y');
}
	
	
/*	
 do
   {
	system("ps all");                                                         //printf("\nresult:%d\n",system("ps all")); 	
	printf("\nEnter the PID of the process to be PAUSED : ");
	  scanf("%d",&p);
	printf("\n***********THE PROCESS : %d , HAS BEEN PAUSED***********\n",p);
        sprintf(pause,"kill -STOP %d",p);                                   
        system(pause);                                                           // printf("\nresult:%d",system(buf));        
       
	printf("\n\nDo you want to resume the process(y/n) : ");
	  scanf(" %c",&a);
	
	if(a=='y')
	{       
        sprintf(resume,"kill -CONT %d",p);
        system(resume);
        printf("\n\n***********THE PROCESS : %d , HAS BEEN RESUMED***********\n\n",p); 
        }
        else
           	exit(0); 
        
        printf("\n\nDo you want to continue(y/n) : ");
          scanf(" %c",&a); 
  
  }
  while(a=='y');    
        	
	return 0;*/






 int AllProcess()
 {
	printf("\n\n=================THE LIST OF ALL PROCESSES IN THE SYSTEM===============\n\n");
	system("ps all");     

 }




 int Paused(char pause[20])
 {
  
	int pid;
	int i=0;
	char a;
	printf("\n\n..................Enter the PIDs of the processes to be PAUSED........................\n\n");
	do
	{
		temp=(struct node*)malloc(sizeof(struct node));
		printf("\nEnter the PID : ");
		scanf("%d",&pid);
		//need function call to check whether the process is already paused
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
	}while(a=='y');  

printf("\n.............................*******..................................\n");




 }


