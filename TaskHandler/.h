#ifndef TaskHandler_h
#define TaskHandler_h
#include "../Run/Run.h"

#define WMSR(description, projectEnd, ...) WeMakeSoftwareRun(description, projectEnd, __VA_ARGS__)

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#endif
