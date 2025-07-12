#ifndef RouterAdapter_h
#define RouterAdapter_h
#include "../IEEE802_3/IEEE802_3.h"

struct ClientDataPointer;

SystemLibrary(RFC1122){
    struct RFC1122Pointer*(*Get)(u8*);
    struct RFC1122Pointer*(*Register)(struct Packet*);
};

#define InitRFC1122 \
        InitSystemLibrary(RFC1122)

#endif