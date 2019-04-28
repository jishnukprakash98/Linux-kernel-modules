#include <linux/module.h>       // Needed by all modules
#include <linux/kernel.h>       // KERN_INFO
#include <linux/sched.h>        // for_each_process, pr_info

MODULE_LICENSE("GPL");

void procs_info_print(void)
{
        struct task_struct* task_list;
        size_t process_counter = 0;
        for_each_process(task_list) {
                pr_info("== name:%s\t\tpid:[%d]\t\tstarttime:[%llu]\t\t\memory:[%llu]\n", task_list->comm, task_list->pid,task_list->real_start_time, task_list->acct_rss_mem1);
                ++process_counter;
                ++process_counter;
        }
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
