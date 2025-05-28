#ifndef System_h
#define System_h
#include "../Run/Run.h"

extern void*GetSystemLibrary(unsigned char*SystemName);

#define SystemSetup(description,CallbackSystemStart,CallbackSystemEnd)\
    struct Application{\
        unsigned char*SystemName;\
        void*(*SystemStart)(void);\
        void*(*SystemEnd)(void);\
        void*SystemLibrary;\
        struct list_head SystemList;\
    };\
    struct Application application;\
    static struct ApplicationProgrammingInterface_##description*InitApplicationProgrammingInterface(void);\
    extern void SystemAdd(struct Application*);\
    static void RunStart(void){\
        application.SystemName=kstrdup(#description, GFP_KERNEL);\
        application.SystemStart=CallbackSystemStart;\
        application.SystemEnd=CallbackSystemEnd;\
        application.SystemLibrary=(void*)InitApplicationProgrammingInterface();\
        INIT_LIST_HEAD(&application.SystemList);\
        SystemAdd(&application);\
    }\
    static void RunEnd(void){\
        list_del(&application.SystemList);\
        kfree(application.SystemName);\
    }\
    RunSetup(description)\
    static struct ApplicationProgrammingInterface_##description*InitApplicationProgrammingInterface(void)

     
#endif