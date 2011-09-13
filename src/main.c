#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/fs.h>

#include "main_private.h"

#define TDDMODULE_DEV_COUNT 1

dev_t tddmodule_first_dev;
tddmodule_dev_t tddmodule_dev;
struct file_operations tddmodule_fops = {
    
};


int tddmodule_setup_cdev(void)
{
    cdev_init(&tddmodule_dev.cdev, &tddmodule_fops);
    tddmodule_dev.cdev.ops = &tddmodule_fops;
    cdev_add(&tddmodule_dev.cdev, tddmodule_first_dev, TDDMODULE_DEV_COUNT); 
    return 0;
}

int tddmodule_init(void)
{

    printk(KERN_DEBUG "Hello, World!");

    if(alloc_chrdev_region(&tddmodule_first_dev, 0, TDDMODULE_DEV_COUNT,
            "tddmodule"))
        goto exit1;
    if(tddmodule_setup_cdev())
        goto exit2;
    return 0;
exit2:
exit1:
    return 1;
}

void tddmodule_exit(void)
{
    unregister_chrdev_region(tddmodule_first_dev, TDDMODULE_DEV_COUNT);
}


module_init(tddmodule_init);
module_exit(tddmodule_exit);

