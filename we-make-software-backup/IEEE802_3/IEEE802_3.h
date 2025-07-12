#ifndef IEEE802_3_h
#define IEEE802_3_h
#include "../NetworkAdapter/NetworkAdapter.h"

struct RFC1122Pointer;

SystemLibrary(IEEE802_3){
   bool(*Receiver)(struct Packet*);
   void(*Continue)(struct Packet*);
   struct Packet*(*Create)(u16,struct RFC1122Pointer*);
   void(*SetType)(struct Packet*, u16);
};

#define InitIEEE802_3 \
        InitSystemLibrary(IEEE802_3)

#endif