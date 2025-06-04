#ifndef ServiceListener_h
#define ServiceListener_h
#include "../Router/Router.h"
struct NetworkAddress;

SystemLibrary(ServiceListener){
    struct ServiceListenerHeader*(*Get)(struct Packet*);
};

#define InitServiceListener\
        InitSystemLibrary(ServiceListener)

#endif
