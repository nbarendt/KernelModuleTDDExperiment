#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "linux/module.h"

extern "C" {
    #include "printkSpy.h"
    ModuleInitFuncPtr __inittest(void);
    ModuleExitFuncPtr __exittest(void);
}

TEST_GROUP(ModuleRegistration)
{
    void setup() {
        mock().ignoreOtherCalls();
        printkSpy_Create();
    }

    void teardown() {
        printkSpy_Destroy();
    }

};

TEST(ModuleRegistration, ModuleRegistersInit)
{
    CHECK(__inittest());
}

TEST(ModuleRegistration, ModuleRegistersExit)
{
    CHECK(__exittest());
}

TEST(ModuleRegistration, ModuleSendsDebugHelloWorld)
{
    __inittest()();
    STRCMP_EQUAL("<7>Hello, World!", printkSpy_get_next());
}
