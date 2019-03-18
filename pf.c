

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



 char pause[20]; 
 char resume[20];
 char a;
 int p[20];
 int r[20];
 int i=0;//stores the no of paused prcesses
 int j=0;//keeps track of the no of resumed processes
 int k=0;//general purpose variable
 int l=0;//general purpose variable
 int t;//general purpose variable
 int c=1;



int main()
{

 do
   {
	system("ps all");  
	     
       
	printf("\n\nDo you want to resume the process(y/n) : ");
	  scanf(" %c",&a);
	
	if(a=='y')
	{       
        sprintf(resume,"kill -CONT %d",p[i]);
        system(resume);
        printf("\n\n***********THE PROCESS : %d , HAS BEEN RESUMED***********\n\n",p[i]); 
        }
        else 
           	exit(0); 
        
        printf("\n\nDo you want to continue(y/n) : ");
          scanf(" %c",&a); 
  
  }
  while(a=='y');    
        	
	return 0;

}




/////////////////////////FUNCTION TO PAUSE PROCESSES //////////////////////////////////////////
void pause()
{

	printf("\n\n..................Enter the PIDs of the processes to be PAUSED........................\n\n");
	do
	{
	  
	  printf("\n\tEnter PID of process No.%d : ",i+1);
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
void resume()
{

int flag;

 if(i==0)
	{
	  	printf("\nAs of yet no process have been paused that can be resumed\n");
	  	
        }
	  
	  
 else  	  
    {
	 
	 printf("\n\n..................Enter the PIDs of the processes to be RESUMED........................\n\n");
	 do
	 {
	  
	  printf("\n\tEnter PID of process No.%d : ",j+1);
	  scanf("%d",&r[j]);
	  flag=check();
	  
	
	  for(k=0;k<i;k++)
	        {
	        	if(r[k]==p[l])
	        	{
	        	        sprintf(resume,"kill -CONT %d",p[i]);
       			        system(resume);
        			printf("The process : %d , has been resumed\n\n",p[i]); 
	   	        }
	   	        else
	   	        	
	   	        
	        
	        }
	  
	  //printf("\n***********THE PROCESS : %d , HAS BEEN PAUSED***********\n",p[i]);
           sprintf(pause,"kill -STOP %d",p[i]);                                   
           system(pause);  
	   i++;
	   printf("\nDo you have another process to pause(y/n) : ");
	   scanf(" %c",&a);
	}while(a=='y');  



}






//////////////////////////////////////////This function checks for errors & exceptions
int check()
{
     for(l=0;l<i;l++)	
      {
	for(k=0;k<j;k++)
	        {
	        	if(r[k]==p[l])
	        	{
	        	        sprintf(resume,"kill -CONT %d",p[i]);
       			        system(resume);
        			printf("The process : %d , has been resumed\n\n",p[i]); 
	   	        }
	   	        else
  			

		}


}



