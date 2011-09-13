#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "printkSpy.h"

extern "C" {
    #include "main.h"
}

TEST_GROUP(LoggingTest)
{
    void setup() {
        mock().ignoreOtherCalls();
    }

    void teardown() {
    }

};

TEST(LoggingTest, ModuleInitGeneratesMessage)
{
    EXPECT_N_LEAKS(1);
    tddmodule_init();
            
}



