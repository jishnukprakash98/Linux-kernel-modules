#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info
#include <linux/sched/signal.h> 
#include <linux/types.h> 
#include <linux/string.h>
#include <linux/timekeeping32.h>
#include <linux/time.h>
#include <linux/timekeeping.h>

MODULE_LICENSE("GPL");

struct list 
{ 
   char name[20];
   int pid; 
   u64 strtime;
   u64 memsize; 
}proc[500];


void procs_info_print(void)
{
        struct task_struct* task_list;
        size_t process_counter = 0;
        	struct timespec ts_start;
	getnstimeofday(&ts_start);
   
        for_each_process(task_list) {       
        	//pr_info("== name:%s\tpid:[%d]\tstarttime:[%llu],[%llu],[%llu]\tmemory:[%llu]\n", task_list->comm,task_list->pid,task_list->start_time,(task_list->utime+task_list->stime),task_list->se.exec_start,task_list->acct_rss_mem1);
        	if((task_list->start_time)>ts_start.tv_nsec && (task_list->acct_rss_mem1)>1000000000)
            		{
            			pr_info("== name:%s\tpid:[%d]\tstarttime:[%llu],[%llu],[%llu]\tmemory:[%llu]\n", task_list->comm,task_list->pid,task_list->start_time,(task_list->utime+task_list->stime),task_list->se.exec_start,task_list->acct_rss_mem1);
			}	
	++process_counter;

        }
	
	printk(KERN_INFO "== Number of process: %zu\n", process_counter);           
        printk(KERN_INFO "== Time: %lu\n", ts_start.tv_nsec);
    
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
