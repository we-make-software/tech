#ifndef ServiceListener_h
#define ServiceListener_h
#include "../Router/Router.h"
struct ServiceListenerHeader{
    u16 Port;
    void(*Function)(struct Packet*);
};

SystemLibrary(ServiceListener){
    
};

#define InitServiceListener\
        InitSystemLibrary(ServiceListener)

#endif
