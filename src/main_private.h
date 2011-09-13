#ifndef TDDMODULE_MAIN_PRIVATE
#define TDDMODULE_MAIN_PRIVATE

#include <linux/cdev.h>

typedef struct {
    struct cdev cdev; /* character device structure */
} tddmodule_dev_t;

#endif
