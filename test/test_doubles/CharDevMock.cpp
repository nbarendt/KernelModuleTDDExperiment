#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include <linux/fs.h>
    #include <linux/cdev.h>
    #include "CharDevMock.h"
    const char *fs_mock_namespace = "mock_fs";
}


int alloc_chrdev_region(dev_t *dev, unsigned    baseminor,
    unsigned    count,
    const char *    name)
{
    unsigned mock_baseminor = baseminor;
    unsigned mock_count = count;

    return mock(fs_mock_namespace).actualCall("alloc_chrdev_region")
        .withParameterOfType("unsigned", "baseminor", &mock_baseminor)
        .withParameterOfType("unsigned", "count", &mock_count)
        .withParameter("name", name)
        .returnValue().getIntValue();
}

void unregister_chrdev_region(dev_t dev, unsigned count)
{
    mock(fs_mock_namespace).actualCall("unregister_chrdev_region")
        .withParameterOfType("unsigned", "dev", &dev)
        .withParameterOfType("unsigned", "count", &count);
}

void cdev_init(struct cdev *cdev, const struct file_operations *fops)
{
    mock(fs_mock_namespace).actualCall("cdev_init")
        .withParameter("cdev", (void*)cdev)
        .withParameter("fops", (void*)fops);
}

int cdev_add(struct cdev *cdev, dev_t dev, unsigned count)
{
    mock(fs_mock_namespace).actualCall("cdev_add")
        .withParameter("cdev", (void*)cdev)
        .withParameterOfType("unsigned", "dev", &dev)
        .withParameterOfType("unsigned", "count", &count);
}
