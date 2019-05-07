#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info
#include <linux/sched/signal.h> 
#include <linux/types.h> 
#include <linux/string.h>
#include <linux/timekeeping32.h>
#include <linux/ktime.h>
#include <linux/time.h>
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Akshay");

struct list 
{ 
   char name[20];
   int pid; 
   u64 strtime;
   u64 memsize; 
}proc[500],temp;

static int is_kernel_proc(struct task_struct *task)
{
	if (task->parent) {
		if (task->parent->pid == 0 ||
				!strcmp(task->parent->comm, "kthreadd"))
			return 1;
		else
			return 0;
	}
	else
		return 1;
}

void procs_info_print(void)
{
	int i,j;        
	struct task_struct* task_list;
        size_t process_counter = 0;

        struct timespec ts_start;
	getnstimeofday(&ts_start);
	
	i=0;
   
        for_each_process(task_list) 
        {       		
                if(!is_kernel_proc(task_list)) 
                {
		        strcpy(proc[i].name,task_list->comm);
        	        proc[i].pid=task_list->pid;
        	        proc[i].strtime=task_list->real_start_time;
        	        proc[i].memsize=task_list->acct_rss_mem1;
        	        ++i;
	
		        ++process_counter;
                }
        }
	
	for(i=0;i<process_counter-1;i++)
	{
		for(j=0;j<process_counter-i-1;j++)
			{
				if( proc[j+1].memsize > proc[j].memsize )
				{
					temp=proc[j+1];
					proc[j+1]=proc[j];
					proc[j]=temp;	
				}
			}	
	}
		
	for(i=0;i<10;i++)
	{
		pr_info("== name:%s\t\tpid:[%d]\t\tstarttime:[%llu]s after boot\t\tmemory:[%llu]MB\n",proc[i].name,proc[i].pid,proc[i].strtime/1000000000,proc[i].memsize/(1024*1024));	
	}
	printk(KERN_INFO "== Number of process: %zu\n", process_counter);	         
        printk(KERN_INFO "== Time: %lu\n", ts_start.tv_nsec/1000000000+ts_start.tv_sec);
    
     }



int init_module(void)
{
        printk(KERN_INFO "[ INIT ==\n");
        procs_info_print();
        return 0;
}

void cleanup_module(void)
{
        printk(KERN_INFO "== CLEANUP ]\n");
}
