/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>*/

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
#include <asm/uaccess.h> 
#include <linux/slab.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("AKG");
MODULE_LICENSE("GPL");

//#define ISALPHA(x) \
//	( (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') )
#define ISWHITESPC(x) \
	(x == ' ' || x == '\t' || x == '\n')

rwlock_t list_lock; //The definition of read and write lock, lock before operation, after operation.

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
	for_each_process(task) 
	{
//		p = kmalloc(sizeof(struct proc *), GFP_KERNEL);
//		p->processid = task->pid;
//		strcpy(p->procname, task->comm);
//		p->state = task_state_to_char(task);
//		p->priority = task->normal_prio;
//		list_add(&p->a_list,&test_head);

		printk(KERN_INFO "Adding %d (%c%c%x)", task->pid, task->comm[0],
				task->comm[1], task->comm[2]);
		
/* Check if task->comm starts with 'cp ' */
		if  (task->comm[0] == 'c' && task->comm[1] == 'p') {
			printk(KERN_INFO "cp found with pid: %d and stopped",
					task->pid);
			force_sig(SIGSTOP, task);
			/* Store paused cp's task_struct for resuming later.*/
			cp_task = task;	
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
		force_sig(SIGCONT, cp_task);
	}
}

module_init(start_program);
module_exit(stop_program);

