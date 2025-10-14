#ifndef TaskHandler_h
#define TaskHandler_h
#include "../Run/Run.h"

#define WMSNAF(name, function) .name = function

#define WMSF(function) .##function = function

#endif
