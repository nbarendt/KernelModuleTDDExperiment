#include "CppUTest/TestHarness.h"

extern "C" {
    #include "printkSpy.h"
}

TEST_GROUP(printkSpyTest)
{
    void setup() {
        printkSpy_Create();
    }

    void teardown() {
        printkSpy_Destroy();
    }

};

TEST(printkSpyTest, SpyMessageListInitiallyEmpty)
{
    CHECK_EQUAL(0, printkSpy_get_len()); 
}

TEST(printkSpyTest, SpyMessageListOfOne)
{
    const char *test_message = {"hello world!"};

    printk(test_message);
    CHECK_EQUAL(1, printkSpy_get_len()); 
}

TEST(printkSpyTest, Can_printk)
{
    const char *test_message = {"hello world!"};

    printk(test_message);
    STRCMP_EQUAL(test_message, printkSpy_get_next());
}

TEST(printkSpyTest, printk_formats)
{
    const char *test_message = {"hello %s!"};

    printk(test_message, "world");
    STRCMP_EQUAL("hello world!", printkSpy_get_next());
}

TEST(printkSpyTest, SpyMessageBufferHoldsMultipleMessages)
{
    const char *test_message_1 = {"hello 1!"};
    const char *test_message_2 = {"hello 2!"};
    const char *test_message_3 = {"hello 3!"};
    
    printk(test_message_1);
    printk(test_message_2);
    printk(test_message_3);
    STRCMP_EQUAL(test_message_1, printkSpy_get_next());
    STRCMP_EQUAL(test_message_2, printkSpy_get_next());
    STRCMP_EQUAL(test_message_3, printkSpy_get_next());
}

