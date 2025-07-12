#ifndef NetworkAdapter_h
#define NetworkAdapter_h
#include "../System/System.h"
#include <linux/ethtool.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/etherdevice.h>
#include <linux/if_ether.h>
#include <linux/workqueue.h>
struct Packet;


struct NetworkAddress{
    u8 Type;
};
struct NetworkLayer{
    struct list_head data;
    struct mutex lock;
};
struct LayerDataPointer{
    u16 ID;
    struct list_head data;
    void(*Destroy)(struct NetworkAddress*);
};
struct NetworkConnection{
    struct LayerDataPointer layerDataPointer;
    struct list_head packet;
    u8 trust;
};
SystemLibrary(NetworkAdapter){
    struct Packet*(*Create)(u16,struct net_device*);
    bool(*Send)(struct Packet*);
    void(*Free)(struct Packet*);
};

#define InitNetworkAdapter\
        InitSystemLibrary(NetworkAdapter)

#define Struct struct __attribute__((packed))  

#define IsLittleEndian (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)

#if IsLittleEndian
    #define ToHost16(x) ntohs(x)
#else
    #define ToHost16(x) (x)
#endif

#endif