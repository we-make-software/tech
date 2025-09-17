#ifndef System_h
#define System_h
#include "../Run/Run.h"


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

#define WeMakeSoftwareRun(description, projectEnd, ...) \
static void WeMakeSoftwareStart(void); \
struct WeMakeSoftware{ \
    unsigned char *name; \
    void (*start)(void); \
    void (*end)(void); \
    void *library; \
    struct list_head list; \
}; \
static struct WeMakeSoftware weMakeSoftware; \
static struct Project_##description* InitProject(void){ \
    static struct Project_##description library={__VA_ARGS__}; \
    return &library; \
} \
extern void WeMakeSoftwareAdd(struct WeMakeSoftware*); \
static void DefaultStart(void){ \
    weMakeSoftware.name=kstrdup(#description, GFP_KERNEL); \
    weMakeSoftware.start=&WeMakeSoftwareStart; \
    weMakeSoftware.end=projectEnd; \
    weMakeSoftware.library=(void*)InitProject(); \
    INIT_LIST_HEAD(&weMakeSoftware.list); \
    WeMakeSoftwareAdd(&weMakeSoftware); \
} \
static void DefaultEnd(void){ \
    list_del(&weMakeSoftware.list); \
    kfree(weMakeSoftware.name); \
} \
Run(description); \
static void WeMakeSoftwareStart(void)


#endif
