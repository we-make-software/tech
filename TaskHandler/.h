#ifndef TaskHandler_h_
#define TaskHandler_h_
#include "../Run/Run.h"

#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#endif
