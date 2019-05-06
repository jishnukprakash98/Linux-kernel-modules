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
#include <linux/hashtable.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Akhileswar");

static struct task_struct *limit_thread;

struct mystruct {
     int data ;
     struct list_head mylist ;
};

struct mystruct *temp;

LIST_HEAD(proc_head) ;

/*The PID of the shell in which we wnat to limit background processes is taken as input parameter*/ 
static int shell_id = 0;
static int limit = 0;

module_param(shell_id, int, S_IRUGO);
module_param(limit, int, S_IRUGO);

/* Return true if task is a kernel process or init.*/
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

int thread_fn(void *a)
{
	static char path_buffer[25];
	static char	 state;
	static char  buf[128];
	static struct task_struct *task;
	static struct file *fil;
	static pid_t  pgrp, session_id;
	static int size, i = 0, j = 0, tpgid = 0, no_of_bg = 0,k=0, count = 0;
	static bool in_array = false;
	static mm_segment_t fs;
	static int *array;

	printk("Shell ID: %d\n", shell_id);

	array = kmalloc(limit * sizeof(int), GFP_KERNEL);

	for(k = 0; k < limit; k++)
		array[k] = 0;



	allow_signal(SIGKILL);


	while (!kthread_should_stop()) { //run infinitely
		for_each_process(task) {

			count = 0;

			if(is_kernel_proc(task)) {
				//printk(KERN_INFO "Kernel Process: %d [%s]",
				//	task->pid, task->comm);
			} else {
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
				i = j = 0;
				
				in_array = false;
				/*Filtering background processes and sending QUIT signal*/
				if(session_id == shell_id && state != 'T' && pgrp != tpgid && task->pid != shell_id) {


					temp = kmalloc(sizeof(struct mystruct), GFP_KERNEL);
					temp->data = task->pid;

					INIT_LIST_HEAD(&temp->mylist);

					//list_add(&temp->mylist,&proc_head);
					
					//struct mystruct *temp;

					/*
					list_for_each_entry(temp, &proc_head, mylist) {
			                        printk(KERN_INFO "Node %d data = %d\n", count, temp->data);
			            
			                }
                                        */
					printk(KERN_INFO "old in_array = %d\n", in_array);
					list_for_each_entry(temp, &proc_head, mylist) {
			            		 
			            		if(temp->data == task->pid){
			            			
			            			in_array = true;
			            			
			            			//printk(KERN_INFO "DUP in_array = %d\n",in_array);
			            		}
                                                printk(KERN_INFO "Node %d data = %d\n",count++, temp->data);
			        	}
			        	printk(KERN_INFO "new in_array = %d\n",in_array);
			        	
			        	
			        	if(in_array == false) {
			        	        printk(KERN_INFO "Adding %d", temp->data);
						list_add(&temp->mylist,&proc_head);
						count++;	
					}
					

				} 		
			}
		}
	/*	
	list_for_each_entry(temp, &proc_head, mylist) {
            printk(KERN_INFO "Node %d data = %d\n",count++, temp->data);
        }
        */
       printk(KERN_INFO "Total Nodes = %d\n", count);
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

	struct mystruct *cursor, *temp;
        /*Deleting the linked list*/
        list_for_each_entry_safe(cursor, temp, &proc_head, mylist) {
            list_del(&cursor->mylist);
            kfree(cursor);
        }

	if (limit_thread) {
		int ret = kthread_stop(limit_thread);

 		if(ret == 0)
  			printk(KERN_INFO "Thread stopped");
	}

}

module_init(start_program);
module_exit(stop_program);



