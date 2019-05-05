#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/moduleparam.h>


MODULE_AUTHOR("Akhil Gokuldas");

MODULE_LICENSE("MIT License");

MODULE_DESCRIPTION("This Module will pause the process given as module parameter(either as process name or pid) when it is inserted into the kernel image and will resume it when it is unloaded from the kernel image"); 

MODULE_VERSION("5.0"); 


static char *proc_any = "HELL";	/* 0 for don't SIGSTOP cp. 1 for stopping. */
struct task_struct *cp_task = NULL;


//module_param(proc_any, char, S_IRUGO); /* Make parameters available. */
module_param(proc_any, charp, S_IRUGO);



static int __init start_program(void)
{

	int flag = 0;
	int i = 0; 
	int k =0;
	int check = 0;  
	int proc_pid = 0;
	struct task_struct *task;	
	
	for (i = 0; proc_any[i] != '\0'; ++i); //For finding the length of proc_any
	
  	i--;
  	
	//printk(KERN_INFO"\n\n%d\n\n",i);   For debugging
	
	for(k = 0; k <= i ; k++) //To check whether the given parameter is the PID
	{
	
		if(proc_any[k] >= '0' && proc_any[k] <= '9')
		{
		
			check = 1;
		}
		
		else
		{
		
			check = 0;
			break;
		}
	}
	
	if(check == 1) //If the input parameter is PID then this section will be executed.
	{
	
		for(k = 0; k <= i ; k++)
		{
		
			proc_pid = proc_pid * 10 + proc_any[k] - '0';
		}
		
		
	        for_each_process(task) 
		{
		
		        //printk("Checking process : %s with PID : %d for match", task->comm, task->pid);
			/* Check if task->comm starts with 'cp ' */
			if(task->pid == proc_pid) 
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
		
			printk(KERN_INFO "\n\nThe given PID does not correspond to an existing process\n\n");
		}	
					
	}
	
	//printk(KERN_INFO"\n\n%d\n\n",proc_pid); Statement for debugging
	else
	{
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
		
			printk(KERN_INFO "\n\nThe given Name does not correspond to an existing process\n\n");
		}
		
	}
	
		
 return 0;
 
}


/*Function to exit from module*/

static void __exit stop_program(void)
{

	if(cp_task != NULL) 
	{
		
		int i = 0; 
		int k =0;
		int check = 0;  
		int proc_pid = 0;
		struct task_struct *task;	
		
		for (i = 0; proc_any[i] != '\0'; ++i); //For finding the length of proc_any
		
	  	i--;
	  	
		//printk(KERN_INFO"\n\n%d\n\n",i);   For debugging
		
		for(k = 0; k <= i ; k++) //To check whether the given parameter is the PID
		{
		
			if(proc_any[k] >= '0' && proc_any[k] <= '9')
			{
			
				check = 1;
			}
			
			else
			{
			
				check = 0;
				break;
			}
		}
		
		
		if(check == 1) //If the input parameter is PID then this section will be executed.
		{
		
			for(k = 0; k <= i ; k++)
			{
			
				proc_pid = proc_pid * 10 + proc_any[k] - '0';
			}
			
			
			for_each_process(task) 
			{
			
				//printk("Checking process : %s with PID : %d for match", task->comm, task->pid);
				/* Check if task->comm starts with 'cp ' */
				if(task->pid == proc_pid) 
				{
				
					printk(KERN_INFO "\n\n%s found with pid : %d and RESUMED \n\n" ,task->comm, task->pid);
					/* Stop the cp process only if asked for when loading module. */
							
					//printk(KERN_INFO "Stopping above process.");
					force_sig(SIGCONT, task);
				}
				
			}
									
		}
		
		//printk(KERN_INFO"\n\n%d\n\n",proc_pid); Statement for debugging
		else
		{
			for_each_process(task) 
			{
			
				//printk("Checking process : %s with PID : %d for match", task->comm, task->pid);
				/* Check if task->comm starts with 'cp ' */
				if(strcmp(task->comm, proc_any) == 0) 
				{
				
					printk(KERN_INFO "\n\n%s found with pid : %d and RESUMED \n\n" ,task->comm, task->pid);
					/* Stop the cp process only if asked for when loading module. */
							
					//printk(KERN_INFO "Stopping above process.");
					force_sig(SIGCONT, task);
				}
			}
	
		}		

	}
	
	printk(KERN_INFO"\n\nMODULE REMOVED\n\n");
	
}


module_init(start_program);

module_exit(stop_program);




