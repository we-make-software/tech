#ifndef RFC8200_h
#define RFC8200_h
#include "../RFC791/RFC791.h"

struct RFC8200NetworkAddress;

SystemLibrary(RFC8200) {
    bool(*Receiver)(struct Packet*);
    void(*Continue)(struct Packet*);
    struct Packet*(*Create)(u16, struct RFC8200NetworkAddress*,struct RFC8200NetworkAddress*);
    void(*SetNextHeader)(struct Packet*, u8);
    u16(*GetTotalLength)(struct Packet*);
    void(*CloneFlowLabel)(struct Packet*, struct Packet*);
    void(*SetFlowLabel)(struct Packet*, u32);
    struct NetworkLayer*(*GetNetworkLayer)(struct NetworkAddress*);
};

#define InitRFC8200 \
    InitSystemLibrary(RFC8200)

#endif