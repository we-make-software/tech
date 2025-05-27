#ifndef Run_h
#define Run_h
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

#define Setup(description) \
    MODULE_DESCRIPTION(#description); \
    MODULE_LICENSE("GPL"); \
    MODULE_AUTHOR("We-Make-Software.Com"); \
    static int __init RunInit(void) { \
        RunStart(); \
        return 0; \
    } \
    static void __exit RunExit(void) { \
        RunExit(); \
    } \
    module_init(RunInit); \
    module_exit(RunExit);
 
#endif    
