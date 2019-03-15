/* Akhileswar */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/ptrace.h>
#include <sys/resource.h>
#include <ulimit.h>
#include <unistd.h>


char str[50];
struct rlimit limit;


int main(int argc, char **argv) {

    if (argc == 2 || argc == 4)
    {
        int pid = atoi(argv[1]);
       /* long ptraceResult = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
        if (ptraceResult < 0)
        {
            printf("Unable to attach to the pid specified\n");
            return -1;
        }
      wait(NULL);
        */
        
        char mapsFilename[1024];
        sprintf(mapsFilename, "/proc/%s/maps", argv[1]);
        FILE* pMapsFile = fopen(mapsFilename, "r");
        
        char statmFilename[1024];
        sprintf(statmFilename, "/proc/%s/statm", argv[1]);
        FILE* pStatmFile = fopen(statmFilename, "r");
        
        char line[256];
        char memory[6];
        int totalMemory = 0;
        
        while (fgets(line, 256, pMapsFile) != NULL)
        {
            unsigned long start_address;
            unsigned long end_address;
            sscanf(line, "%x-%x\n", &start_address, &end_address);
           
           totalMemory += abs(end_address-start_address+1)/1024;
            
           
        }
        
	// printf("MAX CHILD ID IS :%ld\n",sysconf(_SC_CHILD_MAX));

        fgets(memory, 6, pStatmFile);
        printf("\nTotal memory in statm:%dK\n",atoi(memory));
        printf("\nTotal memory calculated:%dK\n",totalMemory);
        
        
        
        fclose(pMapsFile);
        
        fclose(pStatmFile);
        

        //ptrace(PTRACE_CONT, pid, NULL, NULL);
        //ptrace(PTRACE_DETACH, pid, NULL, NULL);
        
        getrlimit(RLIMIT_NPROC, &limit);
    	printf("\nLimit of real user ID %d: %d\n",geteuid(),limit.rlim_cur);
        //printf("\n Result:%d\n",setrlimit(10, &limit));
	limit.rlim_cur = 10;
	setrlimit(RLIMIT_NPROC, &limit);
 	getrlimit(RLIMIT_NPROC, &limit);
    	printf("\nNew Limit of real user ID %d: %d\n",geteuid(),limit.rlim_cur);
    
    }
    
    
    
    else
    {
        printf("%s <pid>\n", argv[0]);
        printf("%s <pid> <ip-address> <port>\n", argv[0]);
        exit(0);
    }
}
