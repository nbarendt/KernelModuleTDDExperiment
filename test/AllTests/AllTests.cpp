#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/MockSupportPlugin.h"


class UnsignedComparator: public MockNamedValueComparator
{
public:
    virtual bool isEqual(void *object1, void *object2)
    {
        return *(unsigned *)object1 == *(unsigned *)object2;
    }
    virtual SimpleString valueToString(void *object)
    {
        return StringFromFormat("%u", *(unsigned *)object);
    }
};

int main(int argc, char *argv[])
{
    UnsignedComparator myUnsignedComparator;
    MockSupportPlugin mockPlugin;


    mockPlugin.installComparator("unsigned", myUnsignedComparator);
    TestRegistry::getCurrentRegistry()->installPlugin(&mockPlugin);

    return CommandLineTestRunner::RunAllTests(argc, argv);
}

