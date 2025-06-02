#ifndef TransportLayer_h
#define TransportLayer_h
#include "../NetworkLayer/NetworkLayer.h"
struct TransportLayerHeader {
    u16 SourcePort;
    u16 DestinationPort;
    u8 Payloader[];
} __attribute__((packed));

SystemLibrary(TransportLayer){
    struct TransportLayerHeader*(*Get)(struct IEEE8023Header*);
 
};

#define InitTransportLayer\
        InitSystemLibrary(TransportLayer)

#endif