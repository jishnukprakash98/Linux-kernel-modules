#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info

MODULE_LICENSE("GPL");

struct list 
{ 
   char name;
   int pid; 
   long  double strtime; 
   long  double memsize; 
}proc[1000];


void procs_info_print(void)
{
        struct task_struct* task_list;
        size_t process_counter = 0;
        
        int i=0,totproc;
        
        for_each_process(task_list) {
                pr_info("== name:%s\t\tpid:[%d]\t\tstarttime:[%llu]\t\tmemory:[%llu]\n", task_list->comm, task_list->pid,task_list->real_start_time, task_list->acct_rss_mem1);

       /* proc[i].name=task_list->comm;
        proc[i].pid=task_list->pid;
        proc[i].strtime=task_list->real_start_time;
        proc[i].memsize=task_list->acct_rss_mem1;
        i++;*/
                ++process_counter;
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
