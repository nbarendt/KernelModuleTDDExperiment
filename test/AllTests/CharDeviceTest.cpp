#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "linux/module.h"
#include "CharDevMock.h"

extern "C" {
    #include "printkSpy.h"
    ModuleInitFuncPtr __inittest(void);
    ModuleExitFuncPtr __exittest(void);
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
