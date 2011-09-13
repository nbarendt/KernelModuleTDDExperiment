#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "CharDevMock.h"

extern "C" {
    #include "linux/module.h"
    #include "linux/fs.h"
    #include "main.h"
}

TEST_GROUP(DeviceReleaseTest)
{
    void setup() {
    }

    void teardown() {
    }
};

TEST(DeviceReleaseTest, fops_has_release)
{
    CHECK(tddmodule_fops.release);
}

TEST(DeviceReleaseTest, release_succeeds)
{
    struct file fil;
    struct inode inode;

    CHECK(!tddmodule_dev_release( &inode, &fil));
}

