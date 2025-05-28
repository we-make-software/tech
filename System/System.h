#ifndef System_h
#define System_h
#include "../Run/Run.h"

#define SystemLibrary(description)\
    struct ApplicationProgrammingInterface_##description

extern void*GetSystemLibrary(unsigned char*SystemName);

#define InitSystemLibrary(description)\
    static struct ApplicationProgrammingInterface_##description*Get##description(void){\
        static struct ApplicationProgrammingInterface_##description*ApplicationProgrammingInterfaceLibrary=NULL;\
        if(!ApplicationProgrammingInterfaceLibrary)\
            ApplicationProgrammingInterfaceLibrary=GetSystemLibrary(#description);\
        return ApplicationProgrammingInterfaceLibrary;\
    }

#define Start\
    static void ProjectStart(void)

#define End\
    static void ProjectEnd(void)

#define BindStart &ProjectStart

#define BindEnd &ProjectEnd    

#define Bind(name) .name=name

#define SystemSetup(description,CallbackSystemStart,CallbackSystemEnd,...)\
    struct Application{\
        unsigned char*SystemName;\
        void(*SystemStart)(void);\
        void(*SystemEnd)(void);\
        void*SystemLibrary;\
        struct list_head SystemList;\
    };\
    struct Application application;\
    static struct ApplicationProgrammingInterface_##description*InitApplicationProgrammingInterface(void){\
        static struct ApplicationProgrammingInterface_##description library={\
            __VA_ARGS__\
        };\
        return &library;\
    }\
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
    RunSetup(description)

     
#endif