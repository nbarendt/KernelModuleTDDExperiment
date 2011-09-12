#ifndef _CUSTOM_MODULE_H
#define _CUSTOM_MODULE_H

typedef int (*ModuleInitFuncPtr) (void);
typedef void (*ModuleExitFuncPtr) (void);

#define module_init(a) \
    ModuleInitFuncPtr __inittest(void) \
    { return a; }

#define module_exit(a) \
    ModuleExitFuncPtr __exittest(void) \
    { return a; }

#endif

