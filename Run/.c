#include ".h"
extern void WeMakeSoftwareStart(void);
extern void WeMakeSoftwareEnd(void);
Void DefaultStart(void){
    WeMakeSoftwareStart();
}
Void DefaultEnd(void){
    WeMakeSoftwareEnd();
}
Run(WeMakeSoftware)
