#ifndef RFC791_h
#define RFC791_h
#include "../RFC1122/RFC1122.h"

struct RFC791NetworkAddress {
    u8 Type;
    u32 Address;
    struct list_head list;
};


SystemLibrary(RFC791) {
    bool(*Receiver)(struct Packet*);
    void(*Continue)(struct Packet*);
    struct Packet*(*Create)(u16,struct RFC791NetworkAddress*);
    bool(*Send)(struct Packet*, struct RFC791NetworkAddress*);
    u16(*GetTotalLength)(struct Packet*);
    void(*SetProtocol)(struct Packet*, u8);
    void(*SetIdentification)(struct Packet*, u16);
    void(*CloneIdentification)(struct Packet*, struct Packet*);
    struct NetworkLayer*(*GetNetworkLayer)(struct NetworkAddress*);
};

#define InitRFC791 \
    InitSystemLibrary(RFC791)

#endif