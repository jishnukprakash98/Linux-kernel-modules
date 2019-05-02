#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/moduleparam.h>


MODULE_AUTHOR("Akhil Gokuldas");
MODULE_LICENSE("MIT License");

static char *proc_any = "HELL";	/* 0 for don't SIGSTOP cp. 1 for stopping. */
struct task_struct *cp_task = NULL;

//module_param(proc_any, char, S_IRUGO); /* Make parameters available. */
module_param(proc_any, charp, S_IRUGO);


static int __init start_program(void)
{
	int flag =0;
	struct task_struct *task;	
	
        for_each_process(task) 
	{
                //printk("Checking process : %s with PID : %d for match", task->comm, task->pid);
		/* Check if task->comm starts with 'cp ' */
		if(strcmp(task->comm, proc_any) == 0) 
		{
			flag = 1;
			printk(KERN_INFO "\n\n%s found with pid : %d and PAUSED \n\n" ,task->comm, task->pid);
			/* Stop the cp process only if asked for when loading module. */
					
			//printk(KERN_INFO "Stopping above process.");
			force_sig(SIGSTOP, task);
			/* Store paused cp's task_struct for resuming later.*/
			cp_task = task;	
		}
	}
	
	if(flag == 0)
	{
	        printk(KERN_INFO "The given Name does not correspond to an existing process.");
	}
		
        return 0;
}

static void __exit stop_program(void)
{
	//int flag = 0;
	/* If cp was found and paused. */
	//printk("\n\nResuming cp pid: %d\n\n", cp_task->pid);
	if(cp_task != NULL) 
	{
		printk(KERN_INFO"\n\nRESUMED process %s with pid : %d \n\n",proc_any, cp_task->pid);
		
		//printk(KERN_INFO "RESUMED process with pid: %d", cp_task->pid);
		force_sig(SIGCONT, cp_task);
		printk(KERN_INFO"\n\nMODULE REMOVED\n\n");
	}
	
}

module_init(start_program);
module_exit(stop_program);


