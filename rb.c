/* Akhileswar*/

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
#include <asm/uaccess.h> 
#include <linux/slab.h>


MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Appu");

/* Return true if task is a kernel process. Return 1 for init. */
static int is_kernel_proc(struct task_struct *task)
{
	if (task->parent) {
		if (task->parent->pid == 0 ||
				!strcmp(task->parent->comm, "kthreadd"))
			return 1;
		else
			return 0;
	}
	return 1;
}

static int __init start_program(void)
{
	static char path_buffer[25];

	int pids[200];
    	
	struct task_struct	*task;
	size_t			bg_proc_count = 0;
	pid_t			pgrp, session_id;
	char			state;
	
	struct file *fil;
	char buf[128];
	mm_segment_t fs;
	int size, i = 0, j = 0, tpgid = 0;
	
	for_each_process(task) {
		if(is_kernel_proc(task)) {
			printk(KERN_INFO "Kernel Process: %d [%s]",
				task->pid, task->comm);
		} else {
			pgrp = pid_vnr(task_pgrp(task));
			session_id = pid_vnr(task_session(task));
			state = task_state_to_char(task);
			
			sprintf(path_buffer,"/proc/%d/stat", task->pid);
			//printk(KERN_INFO "%s\n",path_buffer);
				
			fil = filp_open(path_buffer, O_RDONLY, 0);
			
			if(fil == NULL)
	       		 	printk(KERN_ALERT "rb: filp_open error!!.\n");
	    		else {
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
				//printk(KERN_INFO "rb: buf : %s\n", buf);
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

			if(state != 'T' && pgrp != tpgid) {
				//Background process
				printk(KERN_INFO " Background %5d  %16s",task->pid,task->comm);
				pids[bg_proc_count++] = task->pid;
			} 
		}
	}
	return 0;
}

static void __exit stop_program(void)
{
        
        printk(KERN_INFO "\nFINISHED TESTING...\n");
}

module_init(start_program);
module_exit(stop_program);

