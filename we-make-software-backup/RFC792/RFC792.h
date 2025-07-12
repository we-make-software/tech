#ifndef RFC792_h
#define RFC792_h
#include "../RFC8200/RFC8200.h"

SystemLibrary(RFC792){
    void(*Receiver)(struct Packet*,struct RFC791NetworkAddress*,struct RFC791NetworkAddress*);
};

#define InitRFC792 \
    InitSystemLibrary(RFC792)

#endif