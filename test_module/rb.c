/* Akhileswar*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/signal.h>
#include <linux/sched/signal.h>
#include <linux/dirent.h>
#include <linux/tty.h>
#include <linux/llist.h>
#include <linux/spinlock.h>
#include <asm/uaccess.h> 
#include<linux/slab.h>


MODULE_LICENSE("GPL");
//MODULE_AUTHOR("Appu");

struct linked_list{
    pid_t data;
    struct list_head test_list ;
 } ;


static inline struct tty_struct *get_tty(struct task_struct *task)
{
	struct tty_struct	*tty;
	unsigned long		flags;

	spin_lock_irqsave(&task->sighand->siglock, flags);
	tty = tty_kref_get(task->signal->tty);
	spin_unlock_irqrestore(&task->sighand->siglock, flags);

	return tty;
}

size_t procs_pid(int *p)
{
	struct task_struct	*task = NULL, *task2 = NULL, *task3;
	size_t			process_counter = 0;
	struct tty_struct	*tty = NULL;
	unsigned long		flags;
	pid_t			tpgid;
	
	for_each_process(task) {
/* tty is NULL if process has no controlling tty */
		tpgid = -1;
		tty = get_tty(task);

		if (tty != NULL) {
			//printk(KERN_INFO "tty: %p", tty);
			task2 = pid_task(tty->pgrp, PIDTYPE_PGID);
			//printk(KERN_INFO "task2: %p", task2);
			tpgid = pid_vnr(tty_get_pgrp(tty));
		}
		//printk(KERN_INFO "task2: %p", task2);
		//pr_info("== %s [%d]\n", task->comm, task->pid);
		 p[process_counter++] = task->pid;
		/*Adding proc info to linked list*/
		

//		printk(KERN_INFO "p[%ld] = %d\n",process_counter-1,task->pid);
		printk(KERN_INFO "%d (%s) %c session_id:%d pgrp:%d tpgid:%d",
			task->pid, task->comm, task_state_to_char(task),
			pid_vnr(task_session(task)), pid_vnr(task_pgrp(task)),
			tpgid);
	}
	printk(KERN_INFO "== Number of process: %zu\n", process_counter);

	
	return process_counter;
}

/*
int main(int argc, char *argv[])
{
	
	//FILE *file = NULL;
	
	static char path_buffer[25];
	static int pid = 2;
	static char line[100];
	static char *token;
	static char *name;
	static char state;
	static int count = 0;
	static int pgrp = 0;
	static int tpgid = 0;
	static int session_id = 0;
	int pids[5000];

	/
	struct dirent *dir_entry;
	DIR           *dir;

	node *my_list = list_create(0);
	node head = NULL;
	printf("Background process BELOW:\n");

	
	dir = opendir("/proc/");
	if (dir == NULL) {
		perror("opendir");
		return 1;
	}

	while (dir_entry = readdir(dir)) {
		if (dir_entry->d_name[0] <= '9' &&
				dir_entry->d_name[0] >= '0') {
			pid = atoi(dir_entry->d_name);
			
			//CODE
	*/


	
		
		/*
		file = fopen(path_buffer,"r");
		//if file exists
		if(file != NULL){
			  
			count = 0;
				
			fgets(line,100,file);
				
			name = get_proc_name(line);

			token = strtok(line," ");
			while(token != NULL){
			count++;
			
				if(token[0] == 'S' || token[0] == 'R' || token[0] == 'T' || token[0] == 'I') {
						state = token[0];
				}
				else if(count == 5){
					pgrp = atoi(token);
				}
				else if(count == 6){
					session_id = atoi(token);
				}
				else if(count == 8){
					tpgid = atoi(token);
					break;
				}

				token = strtok(NULL," ");	
			}
			
			//Distinguishing background processes
			if(session_id == 4272  && state != 'T' && pgrp != tpgid) {
					
					//printf("pid:%d %s state:%c sessionID:%d pgrp:%d tpgid:%d\n",pid,name,state,session_id,pgrp,tpgid);
					//list_push(my_list,pid);
					//printf("pid:%5d %-30s Session: %5d \n",pid,name,session_id);
					//kill(pid, SIGQUIT);	
			}
			fclose(file);
			
		}*/
		/*
		list_push(my_list, 1000);
		list_push(my_list, 2000);
		list_push(my_list, 3000);
		printf("Deleted %d",list_pop(my_list,3000));
		

		//list_print(my_list);	
	
	return 0; 
}
*/

static int __init start_bitch(void)
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
	static int session_id = 0;*/
	int pids[200];
	//int i = 0;
	
	/*
	struct file *fil;
	char buf[128];
	mm_segment_t fs;
	*/
	
	
	/* kernel linked list tryout*/
	struct linked_list *p;
	struct linked_list *curr;
	struct list_head test_head;
	struct list_head *ptr;

	INIT_LIST_HEAD(&test_head);
	
	p = kmalloc(sizeof(struct linked_list *),GFP_KERNEL);
	p->data = 999;
	list_add(&p->test_list,&test_head);

	list_for_each(ptr,&test_head){
			curr = list_entry(ptr,struct linked_list,test_list);
			printk(KERN_INFO "\n Hello %d  \n ", curr->data);

		}
	
    	size_t proc_count = procs_pid(pids);
    	printk(KERN_INFO"COME ON...\n");
    	//iterate through the list
    	
	

/*    	printk(KERN_INFO "Generated paths are :\n");
    	for(i = 0; i < proc_count; i++) {
		sprintf(path_buffer,"/proc/%d/stat", pids[i]);
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
			printk(KERN_INFO "buf:%s\n", buf);
		}
	}
		if (fil != NULL)
			filp_close(fil,NULL);
	*/
	/*
		list_for_each_safe(ptr, q, &mylist.list){
		 curr = list_entry(ptr, struct linked_list, list);
		 list_del(ptr);
		 kfree(curr);
	}
*/
	
	
		return 0;
}

static void __exit stop_bitch(void)
{
        
        printk(KERN_INFO "\nFINISHED TESTING...\n");
}

module_init(start_bitch);
module_exit(stop_bitch);

