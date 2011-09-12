#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/fs.h>
#include "main.h"


static dev_t dev;

int tddmodule_init(void)
{

    printk(KERN_DEBUG "Hello, World!");

    if(alloc_chrdev_region(&dev, 0, 1, "tddmodule"))
        goto exit1;
    return 0;

exit1:
    return 1;
}

void tddmodule_exit(void)
{
}


module_init(tddmodule_init);
module_exit(tddmodule_exit);

