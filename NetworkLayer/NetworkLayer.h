#ifndef NetworkLayer_h
#define NetworkLayer_h
#include "../EthernetFrame/EthernetFrame.h"
enum NetworkLayerNextHeader{
    NetworkLayerNextHeader_TransmissionControlProtocol = 6, 
    NetworkLayerNextHeader_UserDatagramProtocol = 17,
    NetworkLayerNextHeader_Unknown
};

SystemLibrary(NetworkLayer){
    enum NetworkLayerNextHeader(*NextHeader)(struct IEEE8023Header*);
    bool(*IsPublic)(struct IEEE8023Header*);
    void(*Receiver)(struct ServiceListenerHeader*, struct RouterHeader*, struct Packet*);
};

#define InitNetworkLayer\
        InitSystemLibrary(NetworkLayer)

#endif