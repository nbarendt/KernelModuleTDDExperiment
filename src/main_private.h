#ifndef TDDMODULE_MAIN_PRIVATE
#define TDDMODULE_MAIN_PRIVATE

#include <linux/cdev.h>

#ifndef __KERNEL__

#include <stdint.h>

typedef uint32_t u32;

#endif

#define TDDMODULE_DEV_CONTROL_RESET 0x1

typedef struct {
    struct cdev cdev; /* character device structure */
} tddmodule_dev_t;

typedef struct {
    volatile u32 control;
    volatile u32 status;
} tddmodule_registers_t;

#endif
