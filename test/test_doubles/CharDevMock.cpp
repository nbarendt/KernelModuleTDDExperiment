#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include <linux/fs.h>
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
