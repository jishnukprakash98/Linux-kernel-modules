#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

	
	char pause[20]; 
	char resume[20];
	char a;
	int p;
	
	
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
        	
	return 0;

}
