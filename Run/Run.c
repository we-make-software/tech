#include "Run.h"
extern void WeMakeSoftwareStart(void);
extern void WeMakeSoftwareEnd(void);
static void DefaultStart(void){
    WeMakeSoftwareStart();
}
static void DefaultEnd(void){
    WeMakeSoftwareEnd();
}
Run(WeMakeSoftware)