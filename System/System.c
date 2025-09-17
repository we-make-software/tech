#include "../Run/Run.h"
struct WeMakeSoftware {
    unsigned char *name;
    void (*start)(void);
    void (*end)(void);
    void *library;
	struct WeMakeSoftware *prev;
};
static LIST_HEAD(list);
void*WeMakeSoftwareGet(unsigned char*);
void*WeMakeSoftwareGet(unsigned char*name){
    struct WeMakeSoftware* wms;
    list_for_each_entry(wms,&list,list){
        if (strcmp(wms->name, name)==0) 
            return wms->library;
    }
    return NULL;
}
EXPORT_SYMBOL(WeMakeSoftwareGet);
void WeMakeSoftwareAdd(struct WeMakeSoftware*);
void WeMakeSoftwareAdd(struct WeMakeSoftware*wms){
    list_add_tail(&wms->list,&list);
}
EXPORT_SYMBOL(WeMakeSoftwareAdd);
void WeMakeSoftwareStart(void);
void WeMakeSoftwareStart(void){
    struct WeMakeSoftware*wms;
    list_for_each_entry(wms,&list,list){
        if(wms->start)
            wms->start();
    }
}
EXPORT_SYMBOL(WeMakeSoftwareStart);
void WeMakeSoftwareEnd(void);
void WeMakeSoftwareEnd(void){
    struct WeMakeSoftware*wms;
    list_for_each_entry_reverse(wms,&list,list){
        if(wms->end)
            wms->end();
    }
}
EXPORT_SYMBOL(WeMakeSoftwareEnd);
static void DefaultStart(void){}
static void DefaultEnd(void){}
Run(System);
