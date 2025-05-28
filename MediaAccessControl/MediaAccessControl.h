#ifndef MediaAccessControl_h
#define MediaAccessControl_h
#include "../NetworkAdapter/NetworkAdapter.h"
SystemLibrary(MediaAccessControl){
    int Receiver(struct sk_buff*skb,struct net_device* dev);
};
#define UseMediaAccessControlLibrary\
        InitSystemLibrary(MediaAccessControl)

#endif