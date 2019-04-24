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
#include<linux/slab.h>


MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Appu");

static int __init start_program(void)
{
        //FILE *file = NULL;
	
	static char path_buffer[25];
	/*
	static int pid = 2;
	static char line[100];
	static char *token;
	static char *name;
	static char state;
	static int count = 0;
	static int pgrp = -1;
	static int tpgid = 0;
	static int session_id = 0;

	int pids[200];
	*/
	
	
    	printk(KERN_INFO"COME ON...\n");
    	
    	
	struct task_struct	*task_list;
	size_t			process_counter = 0;
	pid_t			tpgid;
	
	struct file *fil;
	char buf[128];
	mm_segment_t fs;
	int size;
	
	printk(KERN_INFO "Generated paths are :\n");
	for_each_process(task_list) {
		
		sprintf(path_buffer,"/proc/%d/stat", task_list->pid);
		printk(KERN_INFO "%s\n",path_buffer);
			
		fil = filp_open(path_buffer, O_RDONLY, 0);
		
		if(fil == NULL)
       		 	printk(KERN_ALERT "filp_open error!!.\n");
    		else {
			// Get current segment descriptor
			fs = get_fs();
			// Set segment descriptor associated to kernel space
			set_fs(get_ds());
			// Read the file
			size = fil->f_op->read(fil, buf, 128, &fil->f_pos);
			// Restore segment descriptor
			set_fs(fs);
			// See what we read from file
			buf[size] = '\0';
			printk(KERN_INFO "buf : %s\n", buf);
		}
	
		if (fil != NULL)
			filp_close(fil,NULL);
	
	}

	return 0;
}

static void __exit stop_program(void)
{
        
        printk(KERN_INFO "\nFINISHED TESTING...\n");
}

module_init(start_program);
module_exit(stop_program);

