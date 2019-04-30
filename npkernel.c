#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info
#include <linux/sched/signal.h> 
#include <linux/types.h> 
#include <linux/string.h>

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
        int i=0; 
        int totproc; 
        u64 inittime; 
           
        for_each_process(task_list) {
        
        if (process_counter==0){
        	inittime=task_list->real_start_time;
        }   
        
        	pr_info("== name:%s\tpid:[%d]\tstarttime:[%llu]\tmemory:[%llu]\n", task_list->comm, 						task_list->pid,task_list->real_start_time-inittime, (task_list->acct_rss_mem1+task_list->acct_vm_mem1)/40000000);

        strcpy(proc[i].name,task_list->comm);
        proc[i].pid=task_list->pid;
        proc[i].strtime=task_list->real_start_time;
        proc[i].memsize=task_list->acct_rss_mem1;
        	++i;
                ++process_counter;
        }

        totproc=i;
        printk(KERN_INFO "== Number of process: %zu\n", process_counter);
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
