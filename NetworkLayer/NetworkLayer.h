#ifndef NetworkLayer_h
#define NetworkLayer_h
#include "../EthernetFrame/EthernetFrame.h"
enum NetworkLayerNextHeader{
    NetworkLayerNextHeader_TransmissionControlProtocol = 6, 
    NetworkLayerNextHeader_UserDatagramProtocol = 17,
    NetworkLayerNextHeader_InternetControlMessageProtocolVersion4 = 1,
    NetworkLayerNextHeader_InternetControlMessageProtocolVersion6 = 58,
    NetworkLayerNextHeader_Unknown
};
struct NetworkDataHeader{
    u16 ID;
};
struct ServiceListenerHeader;
struct RouterHeader;
SystemLibrary(NetworkLayer){
    enum NetworkLayerNextHeader(*NextHeader)(struct IEEE8023Header*);
    bool(*IsPublic)(struct IEEE8023Header*);
    void(*Receiver)(struct ServiceListenerHeader*, struct RouterHeader*, struct Packet*);
    struct NetworkDataHeader*(*GetNetworkDataHeader)(struct NetworkAddress*,u16);
};

#define InitNetworkLayer\
        InitSystemLibrary(NetworkLayer)

#endif