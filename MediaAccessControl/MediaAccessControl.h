#ifndef MediaAccessControl_h
#define MediaAccessControl_h
#include "../NetworkAdapter/NetworkAdapter.h"


#ifdef UseReceiver
    struct ReceiverPacket {
        struct sk_buff*skb;
        struct net_device*dev;
        u8*router;
        u8*dataLink;
        u8*networkLayer;
        u8*transportLayer;
        u8*sourceAddress;
        u8*destinationAddress;
        u16*sourcePort;
        u16*destinationPort;
        struct work_struct work;
    };
    struct ReceiverNetworkLayer{
        u8 NextHeader;
        struct list_head list;
    };
#else 
    struct ReceiverPacket;
    struct ReceiverNetworkLayer;
#endif

struct Router;

SystemLibrary(MediaAccessControl){
    int(*Receiver)(struct sk_buff*,struct net_device*);
    struct Router*(*Register)(struct net_device*,u8*,u8*,u16*,struct ReceiverNetworkLayer**);
    struct Router*(*Find)(u8*);
    void(*Hookup)(struct Router*);
    void(*Unhook)(struct Router*);
    int(*Send)(struct sk_buff*,struct Router*);
};

#define UseMediaAccessControlLibrary\
        InitSystemLibrary(MediaAccessControl)

#include "../RFC791/RFC791.h"
#include "../RFC8200/RFC8200.h"
#include "../RFC9293/RFC9293.h"
#include "../RFC8304/RFC8304.h"

#endif