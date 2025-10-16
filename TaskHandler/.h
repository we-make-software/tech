#ifndef TaskHandler_h_Upgrade
#define TaskHandler_h_Upgrade
#include "../Run/Run.h"

#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#define WMSS(description, ...) static struct Project_##description { __VA_ARGS__ };

#endif
#ifdef TaskHandler_h

WMSS(TaskHandler, signature of many functions will go here)

#define GetTaskHandler InitSystemLibrary(TaskHandler)

#endif
