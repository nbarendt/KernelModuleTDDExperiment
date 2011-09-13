#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "linux/module.h"
#include "CharDevMock.h"

extern "C" {
    #include "printkSpy.h"
    #include "main.h"
}

TEST_GROUP(CharDeviceTest)
{
    void setup() {
        printkSpy_Create();
    }

    void teardown() {
        printkSpy_Destroy();
    }

    int initialize_module() {
        return __inittest()();
    }

    void cleanup_module() {
        __exittest()();
    }

};

TEST(CharDeviceTest, ModuleInitAllocatesDevRegion)
{
    unsigned expected_baseminor = 0;
    unsigned expected_count = 1;

    mock(fs_mock_namespace).expectOneCall("alloc_chrdev_region")
        .withParameterOfType("unsigned", "baseminor", &expected_baseminor)
        .withParameterOfType("unsigned", "count", &expected_count)
        .withParameter("name", "tddmodule")
        .andReturnValue(0);
    mock(fs_mock_namespace).ignoreOtherCalls();
    CHECK_EQUAL(0, initialize_module()); 
}

TEST(CharDeviceTest, ModuleInitFailsIfAllocatesDevRegionFails)
{
    unsigned expected_baseminor = 0;
    unsigned expected_count = 1;

    mock(fs_mock_namespace).expectOneCall("alloc_chrdev_region")
        .withParameterOfType("unsigned", "baseminor", &expected_baseminor)
        .withParameterOfType("unsigned", "count", &expected_count)
        .withParameter("name", "tddmodule")
        .andReturnValue(1);
    CHECK_EQUAL(1, initialize_module()); 
}

TEST(CharDeviceTest, ModuleExitReleasesDevRegion)
{
    unsigned expected_count = 1;
    tddmodule_first_dev = 15;

    mock(fs_mock_namespace).expectOneCall("unregister_chrdev_region")
        .withParameterOfType("unsigned", "dev", &tddmodule_first_dev)
        .withParameterOfType("unsigned", "count", &expected_count);
    cleanup_module(); 
}

// struct dev struct

TEST_GROUP(SetupDevStructTest)
{
    void setup() {
    }

    void teardown() {
    }

    int initialize_module() {
        return __inittest()();
    }

    void cleanup_module() {
        __exittest()();
    }
};

TEST(SetupDevStructTest, setup_cdev_calls_cdev_init)
{
    mock(fs_mock_namespace).expectOneCall("cdev_init")
        .withParameter("cdev", (void*)&tddmodule_dev.cdev)
        .withParameter("fops", (void*)&tddmodule_fops);
    mock(fs_mock_namespace).ignoreOtherCalls();
    tddmodule_setup_cdev();
}

TEST(SetupDevStructTest, setup_cdev_initializes_cdev_ops)
{
    mock().ignoreOtherCalls();
    tddmodule_setup_cdev();
    CHECK_EQUAL( &tddmodule_fops, tddmodule_dev.cdev.ops);
}

TEST(SetupDevStructTest, setup_cdev_calls_cdev_add)
{
    unsigned expected_count = 1;
    tddmodule_first_dev = 15;

    mock(fs_mock_namespace).expectOneCall("cdev_init")
        .withParameter("cdev", (void*)&tddmodule_dev.cdev)
        .withParameter("fops", (void*)&tddmodule_fops);

    mock(fs_mock_namespace).expectOneCall("cdev_add")
        .withParameter("cdev", (void*)&tddmodule_dev.cdev)
        .withParameterOfType("unsigned", "dev", &tddmodule_first_dev)
        .withParameterOfType("unsigned", "count", &expected_count);
    tddmodule_setup_cdev();
}

TEST(SetupDevStructTest, ModuleInitInitializes_cdev)
{
    tddmodule_dev.cdev.ops = NULL;
    mock().ignoreOtherCalls();
    initialize_module();
    CHECK_EQUAL( &tddmodule_fops, tddmodule_dev.cdev.ops);
}

// error handling when setup_cdev fails (e.g., unregister)
