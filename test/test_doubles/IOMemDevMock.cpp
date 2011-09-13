#include "CppUTestExt/MockSupport.h"

extern "C" {
    #include "IOMemDevMock.h"
    #include <stdint.h>
    #include <asm/io.h>
    #include <linux/kernel.h>
    const char *iomem_mock_namespace = "mock_iomem";
}

void writel(uint32_t value, void *addr)
{
    mock(iomem_mock_namespace).actualCall("writel")
        .withParameterOfType("unsigned", "value", &value)
        .withParameter("addr", addr);
}

void mb(void)
{
    mock(iomem_mock_namespace).actualCall("mb");
}

unsigned readl(void *addr)
{
    return mock(iomem_mock_namespace).actualCall("readl")
        .withParameter("addr", addr)
        .returnValue().getIntValue();
}
