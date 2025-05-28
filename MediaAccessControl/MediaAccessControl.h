#ifndef MediaAccessControl_h
#define MediaAccessControl_h
#include "../NetworkAdapter/NetworkAdapter.h"

SystemLibrary(MediaAccessControl){
    int(*Receiver)(struct sk_buff*,struct net_device*);
};

#define UseMediaAccessControlLibrary\
        InitSystemLibrary(MediaAccessControl)

#endif