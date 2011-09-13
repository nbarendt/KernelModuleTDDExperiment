#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/kernel.h>

#ifndef __KERNEL__

#include <assert.h>

#endif

#include "main_private.h"

#define TDDMODULE_DEV_COUNT 1

dev_t tddmodule_first_dev;
tddmodule_dev_t tddmodule_dev;
tddmodule_registers_t *tddmodule_registers_p = NULL;

int tddmodule_dev_open (struct inode *inode, struct file *filp)
{
    filp->private_data = &tddmodule_dev;
    iowrite32(TDDMODULE_DEV_CONTROL_RESET, &tddmodule_registers_p->control);
    mb();
    while(!ioread32(&tddmodule_registers_p->status)){
    }
    return 0;
}

int tddmodule_dev_release (struct inode *inode, struct file *filp)
{
    return 0;
}


struct file_operations tddmodule_fops = {
    .open = tddmodule_dev_open,    
    .release = tddmodule_dev_release,
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

#ifndef __KERNEL__
    tddmodule_registers_p = calloc(1, sizeof(tddmodule_registers_t));
    assert(tddmodule_registers_p);
#endif
    return 0;
exit2:
    unregister_chrdev_region(tddmodule_first_dev, TDDMODULE_DEV_COUNT);
exit1:
    return 1;
}

void tddmodule_exit(void)
{
#ifndef __KERNEL__
    free(tddmodule_registers_p);
    tddmodule_registers_p = NULL;
#endif
    unregister_chrdev_region(tddmodule_first_dev, TDDMODULE_DEV_COUNT);
}


module_init(tddmodule_init);
module_exit(tddmodule_exit);

