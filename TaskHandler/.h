#ifndef TaskHandler_h_Upgrade
#define TaskHandler_h_Upgrade
#include "../Run/Run.h"

#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#endif
