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
SystemLibrary(NetworkAdapter){
    struct Packet*(*Create)(u16 size,struct net_device*dev,u8**data) ;
    int(*Send)(struct Packet*);
    void(*Show)(struct Packet*);
    void(*Free)(struct Packet*);
};

#define InitNetworkAdapter\
        InitSystemLibrary(NetworkAdapter)

#endif