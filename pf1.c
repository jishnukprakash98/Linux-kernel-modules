#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{

	//char *buf = malloc(10*sizeof(char));
	char buf[20] = "kill -STOP";
	int p;
	printf("\nresult:%d\n",system("ps all"));      
	
	printf("Enter the desired pid:");
	scanf("%d",&p);
	//char pid[5];
	//itoa(p,pid,10);
	//buf="kill -STOP";                                                          
	//strcat(buf,pid);
	//snprintf (buf, sizeof(buf), "%d",n)
        //printf("Please enter a number:\n");                                        
        //scanf("%d",&a);                                                            
       // printf("Your number is: %d\n",a);                                          
        //snprintf(buf,5, "%d",p);
        sprintf(buf,"kill -STOP %d",p);                                   
        printf("\nresult:%d",system(buf));      
       
	return 0;

}
