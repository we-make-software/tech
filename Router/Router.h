#ifndef Router_h
#define Router_h
#include "../TransportLayer/TransportLayer.h"
struct RouterHeader;
SystemLibrary(Router){
    struct RouterHeader*(*Get)(struct Packet*);
    struct IEEE8023Header*(*CreateVersion4)(u16,struct RouterHeader*,struct Packet**);
    struct IEEE8023Header*(*CreateVersion6)(u16,struct RouterHeader*,struct Packet**);
};
#define InitRouter\
        InitSystemLibrary(Router)

#endif