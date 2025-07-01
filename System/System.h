#ifndef System_h
#define System_h
#include "../Run/Run.h"

#define GlobelList(name) static LIST_HEAD(name)

#define GlobelMutex(name) static DEFINE_MUTEX(name)

#define U16MaxOverflow  65536 

#define u16Max 65535

#define u32Max 4294967295

#define u64Max 18446744073709551615ULL 

#define Struct struct __attribute__((packed))

#define ActionWithArgs(name,...)void(*name)(__VA_ARGS__)

#define CreateActionWithArgs(name,...)static void name(__VA_ARGS__)

#define Action(name)ActionWithArgs(name,void)

#define CreateAction(name)CreateActionWithArgs(name,void)

#define FunctionWithArgs(object,name,...)object(*name)(__VA_ARGS__)

#define CreateFunctionWithArgs(object,name,...)static object name(__VA_ARGS__)

#define Function(object,name)FunctionWithArgs(object,name,void)

#define CreateFunction(object,name)CreateFunctionWithArgs(object,name,void)

#define Bind(name).name=name

#define WeMakeSoftwareLibrary(description)\
    struct Project_##description

extern void*WeMakeSoftwareGet(unsigned char*SystemName);

#define InitSystemLibrary(description)\
    static struct Project_##description*Get##description(void){\
        static struct Project_##description*project=NULL;\
        if(!project)\
            project=WeMakeSoftwareGet(#description);\
        return project;\
    }



#define WeMakeSoftwareRun(description,projectEnd,...)\
    static void WeMakeSoftwareStart(void);\
    struct WeMakeSoftware{\
        unsigned char*name;\
        void(*start)(void);\
        void(*end)(void);\
        void*library;\
        struct list_head list;\
    };\
    struct WeMakeSoftware weMakeSoftware;\
    static struct Project_##description*InitProject(void){\
        static struct Project_##description library={\
            __VA_ARGS__\
        };\
        return &library;\
    }\
    extern void WeMakeSoftwareAdd(struct WeMakeSoftware*);\
    static void DefaultStart(void){\
        weMakeSoftware.name=kstrdup(#description, GFP_KERNEL);\
        weMakeSoftware.start=&WeMakeSoftwareStart;\
        weMakeSoftware.end=projectEnd;\
        weMakeSoftware.library=(void*)InitProject();\
        INIT_LIST_HEAD(&weMakeSoftware.list);\
        WeMakeSoftwareAdd(&weMakeSoftware);\
    }\
    static void DefaultEnd(void){\
        list_del(&weMakeSoftware.list);\
        kfree(weMakeSoftware.name);\
    }\
    Run(description);\
    static void WeMakeSoftwareStart(void)

#endif