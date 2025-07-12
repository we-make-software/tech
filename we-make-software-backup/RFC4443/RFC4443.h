#ifndef RFC4443_h
#define RFC4443_h
#include "../RFC768/RFC768.h"
#include <linux/in6.h>
#include <linux/icmpv6.h>
#include <linux/ipv6.h>
#include <linux/string.h>
SystemLibrary(RFC4443) {
    void(*Receiver)(struct Packet*, struct RFC8200NetworkAddress*, struct RFC8200NetworkAddress*);
};

#define InitRFC4443 \
    InitSystemLibrary(RFC4443)

#endif