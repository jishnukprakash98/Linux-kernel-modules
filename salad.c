#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	long double utime_before=0,stime_before=0,user_util=0,sys_util=0;
        long double time_total=0,time_total_before=0;
        int c=2;
        long double utime,stime;
     
        while(c>0){
        	FILE *file = NULL;
		char path_buffer[25];
		char line[10];
		char *name;
		char state;
        	int pid=atoi(argv[1]);
		int count = 0;
		int pgrp = 0;
        	int priority=0;
        	utime=0;
        	stime=0;
        	long long unsigned int starttime = 0;
        	sprintf(path_buffer,"/proc/%d/stat",pid);
        	file = fopen(path_buffer,"r");
    		count = 0;
			while(fscanf(file,"%s",line))
           	 	{
				count++;
				if(line[0] == '('){
					int len = strlen(line);
					name = (char *)malloc(len * sizeof(char));
					strncpy(name,line,len);
				}
				if(count == 5){
					pgrp = atoi(line);
				}
				if(count == 15){
					stime = atoi(line);
				}
                		if(count == 18){
					priority = atoi(line);
				}
                		if(count == 14){
					utime = atoi(line);
				}
				if(line[0] == 'S' || line[0] == 'R' || line[0] == 'T' || line[0] == 'I'){
					state = line[0];
				}
                		if(count == 22){
					starttime = atoi(line);
                    		break;
                		}
           	 	}
    		printf("\npid:%d %s state:%c priority:%d starttime:%llu utime:%.0Lf pgrp:%d stime:%.0Lf\n",pid,name,state,priority,starttime,utime,pgrp,stime);

   
   
    		long double a[4];
    		FILE *fp;
    		fp = fopen("/proc/stat","r");
    		fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&a[0],&a[1],&a[2],&a[3]);
    		fclose(fp);
    		printf("CPU usage: %.0Lf %.0Lf %.0Lf %.0Lf\n",a[0],a[1],a[2],a[3]);

    		time_total=a[0]+a[1]+a[2]+a[3];
    		printf("\ntime total:%.0Lf\n",time_total);
    	
    		if(c==2)
    		{	
    			utime_before=utime;
    			stime_before=stime;
    			time_total_before=time_total;
        	}
    	
    		sleep(1);
    		c--;
     	 }
	
	
  user_util = 100 * (utime - utime_before) / (time_total - time_total_before);
  sys_util = 100 * (stime - stime_before) / (time_total - time_total_before);
  printf("\nuser_util:%Lf\tsys_util:%Lf \n",user_util,sys_util);
  
  return(0);
  
}
