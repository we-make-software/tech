#ifndef RFC768_h
#define RFC768_h
#include "../RFC9293/RFC9293.h"

SystemLibrary(RFC768){
    void(*RFC791Receiver)(struct Packet*, struct RFC791NetworkAddress*, struct RFC791NetworkAddress*);
    void(*RFC8200Receiver)(struct Packet*, struct RFC8200NetworkAddress*, struct RFC8200NetworkAddress*);
};

#define InitRFC768 \
    InitSystemLibrary(RFC768)

#endif