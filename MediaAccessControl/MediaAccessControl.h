#ifndef MediaAccessControl_h
#define MediaAccessControl_h
#include "../NetworkAdapter/NetworkAdapter.h"
#include "../RFC791/RFC791.h"
#include "../RFC8200/RFC8200.h"

SystemLibrary(MediaAccessControl){
    int(*Receiver)(struct sk_buff*,struct net_device*);
};

#define UseMediaAccessControlLibrary\
        InitSystemLibrary(MediaAccessControl)

#endif