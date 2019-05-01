#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info
#include <linux/sched/signal.h> 
#include <linux/types.h> 
#include <linux/string.h>
#include <linux/timekeeping32.h>

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
        //int i=0; 
        //int totproc; 
           
        for_each_process(task_list) {       
        	pr_info("== name:%s\n\t\t\tpid:[%d]\t\tstarttime:[%llu],[%llu]\t\tmemory:[%llu]\n", task_list->comm,task_list->pid,task_list->start_time/100,task_list->utime+task_list->stime ,task_list->acct_rss_mem1);

        /*strcpy(proc[i].name,task_list->comm);
        proc[i].pid=task_list->pid;
        proc[i].strtime=task_list->real_start_time;
        proc[i].memsize=task_list->acct_rss_mem1;
        	++i;*/
                ++process_counter;
        }

        //totproc=i;
        
        struct timespec ts_start;
        getnstimeofday(&ts_start);
        
        printk(KERN_INFO "== Number of process: %zu\n", process_counter);
        printk(KERN_INFO "== Time: %lu\n", ts_start);
    
     }
/*
        if((task_list->start_time/100)>ts_start && task_list->acct_rss_mem1>30000000000000)
            pr_info("name:%s\t\tpid:[%d]",task_list->comm,task_list->pid);

*/
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
