

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void displayt();
void showt();
int checkt();
void resumet();
void pauset();
void parranget();

 char pause[20]; 
 char resume[20];
 char a;
 int temp;
 int p[20];
 int r[20];
 int i=-1;//stores the no of paused processes
 int j=0;//keeps track of the no of resumed processes
 int k=0;//general purpose variable
 int l=0;//general purpose variable
 int t;//general purpose variable
 int c=1;



int main()
{

int choice;

 do
   {
   
   printf("\n\n.....................ENTER YOUR DESIRED CHOICE.......................\n\n");
   printf("\t1.List of active processes with in the system\n\t2.Pause a process\n\t3.Resume a paused process\n\t4.list of paused process\n");
   printf("\n Enter your choice : ");
   scanf("%d",&choice);
   
   switch(choice)
   {
   	case 1 : displayt();
   		 break;
   	case 2 : pauset();
   		 break;
   	case 3 : resumet();
   		 break;
   	case 4 : showt();
   		 break;
   	default: printf("\n....Invalid Choice.....\n");
   		 break;    
   }
           
        printf("Do you want to continue (y/n) ? :");
        scanf(" %c",&a);   

   }while(a=='y');
}




/////////////////////////FUNCTION TO PAUSE PROCESSES //////////////////////////////////////////
void pauset()
{
l=0;
	printf("\n\n..................Enter the PIDs of the processes to be PAUSED........................\n\n");
	do
	{
	  
	  printf("\n\tEnter PID of process No.%d : ",l+1); 
	  i++;
	  scanf("%d",&p[i]);
	  //printf("\n***********THE PROCESS : %d , HAS BEEN PAUSED***********\n",p[i]);
           sprintf(pause,"kill -STOP %d",p[i]);                                   
           system(pause);  
	   i++;
	  // count++;
	   printf("\nDo you have another process to pause(y/n) : ");
	   scanf(" %c",&a);
	}while(a=='y');  
	

printf("\n.............................*******..................................\n");
//i=0;
}




////////////////////////////FUNCTION TO RESUME THE PAUSED PROCESSES/////////////////////////////
void resumet()
{

int flag;

 if(i==0)
	{
	  	printf("\nAs of yet no process have been paused that can be resumed\n");
	  	exit(0);
        }
	  
	  
 else  	  
    {
	 
	 printf("\n\n..................Enter the PIDs of the processes to be RESUMED........................\n\n");
	 do
	 {
	  
	  printf("\n\tEnter PID of process No.%d : ",j+1);
	  scanf("%d",&temp);//&r[j];
	  flag=checkt();
	  
	
	  for(k=0;k<i;k++)
	        {
	        	if(r[k]==p[l])
	        	{
	        	        sprintf(resume,"kill -CONT %d",p[i]);
       			        system(resume);
        			printf("The process : %d , has been resumed\n\n",p[i]); 
	   	        }
	   	        else
	   	        	continue;
	   	        
	        
	        }
	  
	  //printf("\n***********THE PROCESS : %d , HAS BEEN PAUSED***********\n",p[i]);
           sprintf(pause,"kill -STOP %d",p[i]);                                   
           system(pause);  
	   i++;
	   printf("\nDo you have another process to pause(y/n) : ");
	   scanf(" %c",&a);
	}while(a=='y');  



}


}



//////////////////////////////////////////This function checks for errors & exceptions////////////////////////////////////////////////////////////
int checkt()
{

 int flag=0;
 
     for(l=0;l<=i;l++)	
      {
           
           if(p[l]==temp)           
           {	
           	flag=1;
           	p[l]=-1;
           	break;	
           }	
           else
           	continue;
       }
       
  if(flag==1)
  {
  	parranget();
  	return flag;  
  }
  else
  	printf("\nOnly paused processes can be resumed , the input PID doesn't correspond to that of a paused process..\n");     	
                         
                 
	/*for(k=0;k<j;k++)
	        {
	        	if(r[k]==p[l])
	        	{
	        	        sprintf(resume,"kill -CONT %d",p[i]);
       			        system(resume);
        			printf("The process : %d , has been resumed\n\n",p[i]); 
	   	        }
	   	        else*/
  			

}

//////////////////////////////////THIS FUNCTION REARRANGE P[] AFTER ANY PROCESS HAVE BEEN RESUMED//////////////////////////////////////////////////

void parranget()
 {
  int count=i+1;
  
  for(l=0;l<count;l++)
  {
  	if(l+1<=i)
  	{
  		if(p[l]==-1)
  		{
  			p[l]=p[l+1];
  			p[l+1]=-1;
  		}
  		else
  			continue;
  	}
  	else
  		continue;
	
 }

}

void showt()
{
	l=0;
	int count=i+1;
	if(i=-1)
	{
		printf("\nThe list is empty\n");
	}
	else
	{
	 for(l=0;l<i;l++)
	 {
		printf("Process no %d : %d",count,p[i]);
	 }
	}
}

void displayt()
{
	system("ps all");  
}


