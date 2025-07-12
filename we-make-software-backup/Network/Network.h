#ifndef Network_h
#define Network_h
#include "../RFC9293/RFC9293.h"
#include "../RFC768/RFC768.h"
struct Checksum{
    u16*Data;
    u16 Length;
};

SystemLibrary(Network){
    bool(*Add)(struct NetworkLayer*,void*);
    u16(*ChecksumCalculator)(struct Checksum*,u8);
};

#define InitNetwork \
    InitSystemLibrary(Network)

#endif

    /*
    if (!packet || !packet->skb) {
        printk(KERN_ERR "Send: Packet or skb is NULL, cannot dump.\n");
        return false;
    }

    printk(KERN_INFO "Send: Full SKB data dump (length = %u bytes):\n", packet->skb->len);
    for (unsigned int i = 0; i < packet->skb->len; i++) {
        printk(KERN_CONT "%02x ", packet->skb->data[i]);
        if ((i + 1) % 16 == 0) {
            printk(KERN_CONT "\n");
        }
    }
    printk(KERN_CONT "\n");
    */