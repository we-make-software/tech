#include "../Run/Run.h"
struct Application{
    unsigned char*SystemName;
    void*(*SystemStart)(void);
    void*(*SystemEnd)(void);
    void*SystemLibrary;
    struct list_head SystemList;
};
static LIST_HEAD(SystemList);
void*GetSystemLibrary(unsigned char*SystemName);
void*GetSystemLibrary(unsigned char*SystemName){
    struct Application* application;
    list_for_each_entry(application,&SystemList,SystemList){
        if (strcmp(application->SystemName, SystemName)==0) 
            return application->SystemLibrary;
    }
    return NULL;
}
EXPORT_SYMBOL(GetSystemLibrary);
void SystemAdd(struct Application*application);
void SystemAdd(struct Application*application){
    list_add(&application->SystemList, &SystemList);
}
EXPORT_SYMBOL(SystemAdd);
void SystemStart(void);
void SystemStart(void){
    struct Application*application;
    list_for_each_entry(application,&SystemList,SystemList){
        if(application->SystemStart)
           application->SystemStart();
    }
}
EXPORT_SYMBOL(SystemStart);
void SystemEnd(void);
void SystemEnd(void){
    struct Application*application;
    list_for_each_entry_reverse(application,&SystemList,SystemList){
        if(application->SystemEnd)
            application->SystemEnd();
    }
}
EXPORT_SYMBOL(SystemEnd);
static void RunStart(void){}
static void RunEnd(void){}
RunSetup(System)