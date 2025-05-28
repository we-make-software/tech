#include "Run.h"
extern void SystemStart(void);
extern void SystemEnd(void);
static void RunStart(void){
    SystemStart();
}
static void RunEnd(void){
    SystemEnd();
}
RunSetup(Run)