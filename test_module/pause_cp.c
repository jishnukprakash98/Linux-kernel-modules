/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/tty.h>
#include <linux/llist.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h> 
#include "cp_proc.h"

MODULE_AUTHOR("AKG");
MODULE_LICENSE("GPL");

static int stop_cp = 0;	/* 0 for don't SIGSTOP cp. 1 for stopping. */
module_param(stop_cp, int, S_IRUGO); /* Make parameters available. */

//The definition of read and write lock, lock before operation, after operation
rwlock_t list_lock; 

struct task_struct *cp_task = NULL;

//static DEFINE_RWLOCK(myrwlock);
struct node
{
	int data;
	//struct node *link;
	struct list_head p_list ;
};
//struct node *head = NULL,*current = NULL,*temp = NULL;

struct proc
{
	int processid;
	char procname[100];
	char state;
	int priority;
	struct list_head a_list ;
};
//struct proc *head2 = NULL,*current2 = NULL,*temp2 = NULL;

static int __init start_program(void)
{
	struct task_struct	*task;
	pid_t			pid;
	//char			state;
	//int			normal_prio;
	
	struct proc *p = NULL;
	struct proc *curr,*temp;
	//struct list_head test_head;
	struct list_head *ptr;

	//INIT_LIST_HEAD(&test_head);
//	LIST_HEAD(test_head);
	
/*	write_lock(&list_lock);
 *
	write_unlock(&list_lock);
	
	write_lock(&list_lock);*/
/*	list_for_each_entry(curr, &test_head, a_list)
    	{
        	printk(KERN_INFO "Testing:%d\n",curr->processid);
    	}*/
//	write_unlock(&list_lock);
	
	printk(KERN_INFO "cp: Option to SIGSTOP cp enabled by default? %s",
		(stop_cp) ? "YES" : "NO");

	for_each_process(task) 
	{
//		p->processid = task->pid;
//		strcpy(p->procname, task->comm);
//		p->state = task_state_to_char(task);
//		p->priority = task->normal_prio;
//		list_add(&p->a_list,&test_head);

		printk(KERN_INFO "Adding %d (%s)", task->pid, task->comm);

/* Check if task->comm starts with 'cp ' */
		if (strcmp(task->comm, "cp") == 0) {
			printk(KERN_INFO "%s found with pid: %d and stopped",
				task->comm, task->pid);
/* Stop the cp process only if asked for when loading module. */
			if (stop_cp) {
				printk(KERN_INFO "Stopping above process.");
				force_sig(SIGSTOP, task);
			/* Store paused cp's task_struct for resuming later.*/
//				cp_task = task;	
			}
		}
	}
//	write_lock(&list_lock);

/*	list_for_each_entry_safe(curr,temp,&test_head,a_list)
	{
	 	printk(KERN_INFO "EJECTING %s", curr->procname);
	 	
	 	list_del(&curr->a_list);
        	kfree(curr);
	}*/
//	write_unlock(&list_lock);
	return 0;
}

static void __exit stop_program(void)
{
	/* If cp was found and paused. */
	if (cp_task != NULL) {
		printk(KERN_INFO "Resuming cp pid: %d", cp_task->pid);
		//force_sig(SIGCONT, cp_task);
	}
}

module_init(start_program);
module_exit(stop_program);
