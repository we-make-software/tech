#ifndef RFC9293_h
#define RFC9293_h
#include "../RFC792/RFC792.h"

SystemLibrary(RFC9293){
    void(*RFC791Receiver)(struct Packet*, struct RFC791NetworkAddress*,struct RFC791NetworkAddress*);
    void(*RFC8200Receiver)(struct Packet*, struct RFC8200NetworkAddress*,struct RFC8200NetworkAddress*);
};

#define InitRFC9293 \
    InitSystemLibrary(RFC9293)

#endif