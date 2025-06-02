#ifndef EthernetFrame_h
#define EthernetFrame_h
#include "../NetworkAdapter/NetworkAdapter.h"
struct IEEE8023Header {
    u8 DestinationAddress[6];
    u8 SourceAddress[6];
    u16 Type;
    u8 PayLoader[];
} __attribute__((packed));

SystemLibrary(EthernetFrame){
    struct net_device*(*PhysicalLayer)(struct Packet*);
    struct IEEE8023Header*(*DataLinkLayer)(struct Packet*);
    bool(*IsGlobel)(struct IEEE8023Header*);
    bool(*IsVersion4)(struct IEEE8023Header*);
    void(*Receiver)(struct Packet*);
    struct IEE8023HeaEder*(*CreateVersion4)(u16,struct net_device*,struct Packet**);
    struct IEEE8023Header*(*CreateVersion6)(u16,struct net_device*,struct Packet**);
    int(*Send)(struct Packet*);
};

#define InitEthernetFrame\
        InitSystemLibrary(EthernetFrame)

#endif