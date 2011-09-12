#include <linux/printk.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void printkSpy_Create(void);
void printkSpy_Destroy(void);
int printkSpy_get_len(void);
const char *printkSpy_get_next(void);


