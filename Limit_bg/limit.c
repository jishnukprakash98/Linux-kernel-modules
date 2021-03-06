#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/sched/signal.h>
#include <linux/tty.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/delay.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akhileswar");

static struct task_struct *limit_thread;

struct proc_data{
     int data ;
     struct task_struct *process;
     struct list_head mylist ;
};

/* Initialise proc_head as the head of the linked list*/
LIST_HEAD(proc_head) ;

/*The PID of the shell in which we wnat to limit background processes is taken as input parameter*/ 
static int shell = 0;
static int limit = 0;

module_param(shell, int, S_IRUGO);
module_param(limit, int, S_IRUGO);

/*	
	Input : Pointer to task_struct of a task/process.
	Returns true if task is a kernel process or init.
*/
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

/* This function is spawned as a thread. Takes void pointer a parameter. */
int thread_fn(void *a)
{
	static char path_buffer[25];
	static char state;
	static char  buf[128];
	static struct task_struct *task;
	static struct file *fil;
	static pid_t  pgrp, session_id;
	static int size, i = 0, j = 0, tpgid = 0, count = 0, c = 0;
	static bool in_array = false;
	static mm_segment_t fs;
	
	struct proc_data*temp = NULL;
	struct proc_data*cursor = NULL;
	struct proc_data*tm = NULL;

	printk("Shell ID: %d\n", shell);

	allow_signal(SIGKILL);

	while (!kthread_should_stop()) {
		
		count = 0;

		for_each_process(task) {

			if(!is_kernel_proc(task)) {
				
				pgrp = pid_vnr(task_pgrp(task));
				session_id = pid_vnr(task_session(task));
				state = task_state_to_char(task);

				sprintf(path_buffer,"/proc/%d/stat", task->pid);

				fil = filp_open(path_buffer, O_RDONLY, 0);

				if(fil == NULL) {
		       		 	printk(KERN_ALERT "rb: filp_open error!!.\n");
		       	} else {
					// Get current segment descriptor
					fs = get_fs();
					// Set segment descriptor associated to kernel space
					set_fs(get_ds());
					// Read the file
					size = fil->f_op->read(fil, buf, 128,
							&fil->f_pos);
					// Restore segment descriptor
					set_fs(fs);
					// See what we read from file
					buf[size] = '\0';
				}
				if (fil != NULL)
					filp_close(fil, NULL);

				tpgid = 0;
				/* Get tpgid (8th field sep by ' ') from stat file. */
				while (i < 128) {
					if (buf[i] == ' ') {
						if (j == 7)
							break; /* If reached 8th ' '. */
						++j; /* j is no: of spaces read. */
						++i;
						continue;
					}
					if (j == 7 && buf[i] != ' ') {
						if (buf[i] == '-') { /* -ve */
							tpgid = -1; /* No tpgid. */
							break;
						}
						else	/* Convert to number. */
							tpgid = tpgid * 10 + (buf[i] - '0');
					}
					++i;
				}
				i = j = 0;	// For next iteration.
				
				in_array = false;
				/*Filtering background processes and sending QUIT signal*/
				if(session_id == shell && state != 'T' && pgrp != tpgid && task->pid != shell) {
					
					if(list_empty(&proc_head) == 0) {
                                        
						struct proc_data *cur;
						list_for_each_entry(cur, &proc_head, mylist) {
				            		 
				            if(cur->data == task->pid)
				            	in_array = true;			
				        }
				    }   	
			        if(in_array == false) {
			        	temp = kmalloc(sizeof(struct proc_data), GFP_KERNEL);
						temp->data = task->pid;
						temp->process = task;
			        		
						list_add(&temp->mylist,&proc_head);
						count++;	
					}
					
				} 		
			} 
			
		}
		

        if(count > limit) {
        	c = 0;
        	list_for_each_entry(temp, &proc_head, mylist) {
        		c++;
        		
        		if(c > limit) {
        			force_sig(SIGTERM, temp->process);
        			printk(KERN_INFO "Killed %s %d since limit = %d",temp->process->comm, temp->data, limit);
        		}
        	}

        }

        /*Deleting the linked list*/
        list_for_each_entry_safe(cursor, tm, &proc_head, mylist) {
            list_del(&cursor->mylist);
            kfree(cursor);
        }
       
        ssleep(2);
	}

	return 0;
}

static int __init start_program(void)
{

	limit_thread = kthread_create(thread_fn, NULL, "limit_thread");

	if(limit_thread) 
		wake_up_process(limit_thread);

	return 0;
}

static void __exit stop_program(void)
{

	if (limit_thread) {
		int ret = kthread_stop(limit_thread);

 		if(ret == 0)
  			printk(KERN_INFO "Thread stopped");
	}

}

module_init(start_program);
module_exit(stop_program);

static void __exit stop_program(void)
{

	if (limit_thread) {
		int ret = kthread_stop(limit_thread);

 		if(ret == 0)
  			printk(KERN_INFO "Thread stopped");
	}

}

module_init(start_program);
module_exit(stop_program);
